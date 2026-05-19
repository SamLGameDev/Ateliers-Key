/**************************************************************************************
*                                                                                     *
* Copyright   2023-2025 by Heathen Engineering Limited, an Irish registered company   *
* # 556277, VAT IE3394133CH, contact Heathen via support@heathen.group                *
*                                                                                     *
***************************************************************************************/

#include "UploadLeaderboardScoreAsyncTask.h"

UUploadLeaderboardScoreAsyncTask* UUploadLeaderboardScoreAsyncTask::SteamUploadLeaderboardScoreDetails(int64 boardId, bool keepBest, int32 score, TArray<int32> data)
{
    UUploadLeaderboardScoreAsyncTask* Node = NewObject<UUploadLeaderboardScoreAsyncTask>();
    Node->Board = boardId;
    Node->KeepBest = keepBest;
    Node->Score = score;
    Node->Data = data;
    return Node;
}

UUploadLeaderboardScoreAsyncTask* UUploadLeaderboardScoreAsyncTask::SteamUploadLeaderboardScore(int64 boardId, bool keepBest, int32 score)
{
    UUploadLeaderboardScoreAsyncTask* Node = NewObject<UUploadLeaderboardScoreAsyncTask>();
    Node->Board = boardId;
    Node->KeepBest = keepBest;
    Node->Score = score;
    Node->Data = TArray<int32>();
    return Node;
}

void UUploadLeaderboardScoreAsyncTask::Activate()
{
    if (SteamAPI_Init())
    {
        SteamLeaderboard_t board = static_cast<SteamLeaderboard_t>(Board);
        ELeaderboardUploadScoreMethod method = KeepBest ? ELeaderboardUploadScoreMethod::k_ELeaderboardUploadScoreMethodKeepBest : ELeaderboardUploadScoreMethod::k_ELeaderboardUploadScoreMethodForceUpdate;

        SteamAPICall_t handle = SteamUserStats()->UploadLeaderboardScore(board, method, Score, Data.GetData(), Data.Num());
        m_LeaderboardScoreUploaded_t.Set(handle, this, &UUploadLeaderboardScoreAsyncTask::HandleUploadScore);
    }
    else
    {
        Failed.Broadcast(false, 0, 0);
        SetReadyToDestroy();
    }
}

void UUploadLeaderboardScoreAsyncTask::HandleUploadScore(LeaderboardScoreUploaded_t* Response, bool bIOError)
{
    FGraphEventRef GameThreadTask = FFunctionGraphTask::CreateAndDispatchWhenReady([this, bIOError, Response]()
        {
            if (!bIOError)
            {
                if (Response->m_bSuccess == 1)
                    Success.Broadcast(Response->m_bScoreChanged == 1, Response->m_nGlobalRankNew, Response->m_nGlobalRankPrevious);
                else
                    Failed.Broadcast(false, 0, 0);
            }
            else
            {
                IOError.Broadcast(false, 0, 0);
            }
        }, TStatId(), nullptr, ENamedThreads::GameThread);
    GameThreadTask->Wait();
    SetReadyToDestroy();
}
