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
#include "UploadLeaderboardScoreAsyncTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FLeaderboardScoreUploadedTaskDelegate, bool, scoreChanged, int32, newRank, int32, oldRank);

UCLASS()
class TOOLKITSTEAMWORKS_API UUploadLeaderboardScoreAsyncTask : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FLeaderboardScoreUploadedTaskDelegate Success;
    UPROPERTY(BlueprintAssignable)
    FLeaderboardScoreUploadedTaskDelegate Failed;
    UPROPERTY(BlueprintAssignable, meta = (DisplayName = "IO Error"))
    FLeaderboardScoreUploadedTaskDelegate IOError;

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Upload Leaderboard Score & Details - Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|User Stats")
    static UUploadLeaderboardScoreAsyncTask* SteamUploadLeaderboardScoreDetails(int64 boardId, bool keepBest, int32 score, TArray<int32> data);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Upload Leaderboard Score - Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|User Stats")
    static UUploadLeaderboardScoreAsyncTask* SteamUploadLeaderboardScore(int64 boardId, bool keepBest, int32 score);

    void Activate() override;

private:
    CCallResult<UUploadLeaderboardScoreAsyncTask, LeaderboardScoreUploaded_t> m_LeaderboardScoreUploaded_t;
    // ReSharper disable once CppUE4ProbableMemoryIssuesWithUObject
    UObject* WorldContextObject;
    int64 Board;
    bool KeepBest;
    int32 Score;
    TArray<int32> Data;

    void HandleUploadScore(LeaderboardScoreUploaded_t* Response, bool bIOError);
};