/**************************************************************************************
*                                                                                     *
* Copyright   2023-2025 by Heathen Engineering Limited, an Irish registered company   *
* # 556277, VAT IE3394133CH, contact Heathen via support@heathen.group                *
*                                                                                     *
***************************************************************************************/

#include "UGCDownloadTask.h"

UUGCDownloadTask* UUGCDownloadTask::SteamUGCDownloadTask(int64 ugcHandle, int32 priority)
{
    UUGCDownloadTask* Node = NewObject<UUGCDownloadTask>();
    Node->Handle = static_cast<UGCHandle_t>(ugcHandle);
    Node->Priority = static_cast<uint32>(priority);
    return Node;
}

void UUGCDownloadTask::Activate()
{
    SteamAPICall_t handle = SteamRemoteStorage()->UGCDownload(Handle, Priority);
    m_RemoteStorageDownloadUGCResult_t.Set(handle, this, &UUGCDownloadTask::HandleDownload);
}

void UUGCDownloadTask::HandleDownload(RemoteStorageDownloadUGCResult_t* Response, bool bIOError)
{
	if (!bIOError)
	{
		FGraphEventRef GameThreadTask = FFunctionGraphTask::CreateAndDispatchWhenReady([this, Response]()
			{
				Success.Broadcast(static_cast<UEResult>(Response->m_eResult), static_cast<int>(Response->m_nAppID), Response->m_nSizeInBytes, FString(Response->m_pchFileName), static_cast<int64>(Response->m_ulSteamIDOwner));
			}, TStatId(), nullptr, ENamedThreads::GameThread);
		GameThreadTask->Wait();
	}
	else
	{
		// Execute the delegate on the game thread asynchronously
		FGraphEventRef GameThreadTask = FFunctionGraphTask::CreateAndDispatchWhenReady([this]()
			{
				IOError.Broadcast(UEResult::EPC_IOFailure, 0, 0, FString(), 0);
			}, TStatId(), nullptr, ENamedThreads::GameThread);
		GameThreadTask->Wait();
	}
	SetReadyToDestroy();
}
