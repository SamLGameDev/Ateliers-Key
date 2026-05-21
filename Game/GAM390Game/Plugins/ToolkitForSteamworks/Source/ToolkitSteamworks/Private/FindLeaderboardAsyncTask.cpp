/**************************************************************************************
*                                                                                     *
* Copyright   2023-2025 by Heathen Engineering Limited, an Irish registered company   *
* # 556277, VAT IE3394133CH, contact Heathen via support@heathen.group                *
*                                                                                     *
***************************************************************************************/

#include "FindLeaderboardAsyncTask.h"

UFindLeaderboardAsyncTask* UFindLeaderboardAsyncTask::SteamFindLeaderboard(FString apiName)
{
    UFindLeaderboardAsyncTask* Node = NewObject<UFindLeaderboardAsyncTask>();
    Node->ApiName = apiName;
    Node->CreateIfMissing = false;
    return Node;
}

UFindLeaderboardAsyncTask* UFindLeaderboardAsyncTask::SteamFindOrCreateLeaderboard(FString apiName, UELeaderboardSortMethod sortMethod, UELeaderboardDisplayType displayType)
{
    UFindLeaderboardAsyncTask* Node = NewObject<UFindLeaderboardAsyncTask>();
    Node->ApiName = apiName;
    Node->CreateIfMissing = true;
    Node->SortMethod = sortMethod;
    Node->DisplayType = displayType;
    return Node;
}

void UFindLeaderboardAsyncTask::Activate()
{
    if (SteamAPI_Init())
    {
        if (!CreateIfMissing)
        {
            SteamAPICall_t handle = SteamUserStats()->FindLeaderboard(StringCast<ANSICHAR>(*ApiName).Get());
            m_LeaderboardFindResult_t.Set(handle, this, &UFindLeaderboardAsyncTask::HandleFind);
        }
        else
        {
            SteamAPICall_t handle = SteamUserStats()->FindOrCreateLeaderboard(StringCast<ANSICHAR>(*ApiName).Get(), static_cast<ELeaderboardSortMethod>(SortMethod), static_cast<ELeaderboardDisplayType>(DisplayType));
            m_LeaderboardFindResult_t.Set(handle, this, &UFindLeaderboardAsyncTask::HandleFind);
        }
    }
    else
    {
        Failed.Broadcast(0);
        SetReadyToDestroy();
    }
}

void UFindLeaderboardAsyncTask::HandleFind(LeaderboardFindResult_t* Response, bool bIOError)
{
	if (!bIOError)
	{
		int64 boardId = static_cast<int64>(Response->m_hSteamLeaderboard);
		bool found = Response->m_bLeaderboardFound > 0 ? true : false;

		FGraphEventRef GameThreadTask = FFunctionGraphTask::CreateAndDispatchWhenReady([this, boardId, found]()
			{
                if (found)
                    Success.Broadcast(boardId);
                else
                    Failed.Broadcast(boardId);
			}, TStatId(), nullptr, ENamedThreads::GameThread);
		GameThreadTask->Wait();
	}
	else
	{
		// Execute the delegate on the game thread asynchronously
		FGraphEventRef GameThreadTask = FFunctionGraphTask::CreateAndDispatchWhenReady([this]()
			{
                IOError.Broadcast(0);
			}, TStatId(), nullptr, ENamedThreads::GameThread);
		GameThreadTask->Wait();
	}
    SetReadyToDestroy();
}
