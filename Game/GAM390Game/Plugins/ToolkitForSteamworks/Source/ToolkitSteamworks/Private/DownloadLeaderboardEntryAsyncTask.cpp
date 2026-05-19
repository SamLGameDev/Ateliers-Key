/**************************************************************************************
*                                                                                     *
* Copyright   2023-2025 by Heathen Engineering Limited, an Irish registered company   *
* # 556277, VAT IE3394133CH, contact Heathen via support@heathen.group                *
*                                                                                     *
***************************************************************************************/

#include "DownloadLeaderboardEntryAsyncTask.h"

UDownloadLeaderboardEntryAsyncTask* UDownloadLeaderboardEntryAsyncTask::SteamDownloadLeaderboardEntries(int64 boardId, UELeaderboardDataRequest requestType, int32 start, int32 end, int32 detailCount)
{
    UDownloadLeaderboardEntryAsyncTask* Node = NewObject<UDownloadLeaderboardEntryAsyncTask>();
    Node->ForUsers = false;
    Node->Board = static_cast<SteamLeaderboard_t>(boardId);
    Node->Request = static_cast<ELeaderboardDataRequest>(requestType);
    Node->Start = start;
    Node->End = end;
    Node->DetailCount = detailCount;
    Node->Users = TArray<CSteamID>();
    return Node;
}

UDownloadLeaderboardEntryAsyncTask* UDownloadLeaderboardEntryAsyncTask::SteamDownloadLeaderboardEntriesForUsers(int64 boardId, TArray<int64> users, int32 detailCount)
{
    UDownloadLeaderboardEntryAsyncTask* Node = NewObject<UDownloadLeaderboardEntryAsyncTask>();
    Node->ForUsers = true;
    Node->Board = static_cast<SteamLeaderboard_t>(boardId);
    Node->Request = ELeaderboardDataRequest::k_ELeaderboardDataRequestGlobal;
    Node->Start = 0;
    Node->End = 0;
    Node->DetailCount = detailCount;
    Node->Users = TArray<CSteamID>();
    int numUsers = users.Num();
    for (int i = 0; i < numUsers; i++)
    {
        Node->Users.Add(INT64_TO_STEAMID(users[i]));
    }
    return Node;
}

void UDownloadLeaderboardEntryAsyncTask::Activate()
{
    if (SteamAPI_Init())
    {
        if (ForUsers)
        {
            SteamAPICall_t handle = SteamUserStats()->DownloadLeaderboardEntriesForUsers(Board, Users.GetData(), Users.Num());
            m_LeaderboardScoresDownloaded_t.Set(handle, this, &UDownloadLeaderboardEntryAsyncTask::HandleResults);
        }
        else
        {
            SteamAPICall_t handle = SteamUserStats()->DownloadLeaderboardEntries(Board, Request, Start, End);
            m_LeaderboardScoresDownloaded_t.Set(handle, this, &UDownloadLeaderboardEntryAsyncTask::HandleResults);
        }
    }
    else
    {
        IOError.Broadcast(TArray<FLeaderboardEntry>());
        SetReadyToDestroy();
    }
}

void UDownloadLeaderboardEntryAsyncTask::HandleResults(LeaderboardScoresDownloaded_t* Response, bool bIOError)
{
    FGraphEventRef GameThreadTask = FFunctionGraphTask::CreateAndDispatchWhenReady([this, bIOError, Response]()
        {
            TArray<FLeaderboardEntry> results;

            if (!bIOError)
            {
                for (int i = 0; i < Response->m_cEntryCount; i++)
                {
                    LeaderboardEntry_t* entry = new LeaderboardEntry_t;
                    int32* details = new int32[DetailCount];
                    if (SteamUserStats()->GetDownloadedLeaderboardEntry(Response->m_hSteamLeaderboardEntries, i, entry, details, DetailCount))
                    {
                        FLeaderboardEntry nEntry = FLeaderboardEntry();
                        if (DetailCount > 0)
                        {
                            for (int ii = 0; ii < DetailCount; ii++)
                            {
                                nEntry.Details.Add(details[ii]);
                            }
                        }
                        delete[] details;

                        nEntry.Rank = entry->m_nGlobalRank;
                        nEntry.Score = entry->m_nScore;
                        nEntry.UgcHandle = static_cast<int64>(entry->m_hUGC);
                        nEntry.UserId = STEAMID_TO_INT64(entry->m_steamIDUser);

                        delete entry;
                        results.Add(nEntry);
                    }
                    else
                    {
                        delete entry;
                        delete[] details;
                    }
                }
                Complete.Broadcast(results);
            }
            else
            {
                IOError.Broadcast(results);
            }
        }, TStatId(), nullptr, ENamedThreads::GameThread);
    GameThreadTask->Wait();
    SetReadyToDestroy();
}
