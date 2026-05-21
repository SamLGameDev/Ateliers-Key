/**************************************************************************************
*                                                                                     *
* Copyright   2023-2025 by Heathen Engineering Limited, an Irish registered company   *
* # 556277, VAT IE3394133CH, contact Heathen via support@heathen.group                *
*                                                                                     *
***************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "SteamToolsSubsystem.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UGCDownloadTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FRemoteStorageDownloadUGCTaskResult, UEResult, Result, int, AppId, int, FileSize, FString, FileName, int64, Owner);

UCLASS()
class TOOLKITSTEAMWORKS_API UUGCDownloadTask : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
        FRemoteStorageDownloadUGCTaskResult Success;
    UPROPERTY(BlueprintAssignable, meta = (DisplayName = "IO Error"))
        FRemoteStorageDownloadUGCTaskResult IOError;

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "UGC Download - Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|Remote STorage")
        static UUGCDownloadTask* SteamUGCDownloadTask(int64 ugcHandle, int32 priority);

    void Activate() override;

    /*
    * 	EResult m_eResult;				// The result of the operation.
    UGCHandle_t m_hFile;			// The handle to the file that was attempted to be downloaded.
    AppId_t m_nAppID;				// ID of the app that created this file.
    int32 m_nSizeInBytes;			// The size of the file that was downloaded, in bytes.
    char m_pchFileName[k_cchFilenameMax];		// The name of the file that was downloaded.
    uint64 m_ulSteamIDOwner;		// Steam ID of the user who created this content.
    */

private:
    CCallResult<UUGCDownloadTask, RemoteStorageDownloadUGCResult_t> m_RemoteStorageDownloadUGCResult_t;

    // ReSharper disable once CppUE4ProbableMemoryIssuesWithUObject
    UObject* WorldContextObject;
    UGCHandle_t Handle;
    uint32 Priority;

    void HandleDownload(RemoteStorageDownloadUGCResult_t* Response, bool bIOError);
};