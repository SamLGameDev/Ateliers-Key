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
#include "FindLeaderboardAsyncTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLeaderboardFindTaskResult, int64, boardId);

UCLASS()
class TOOLKITSTEAMWORKS_API UFindLeaderboardAsyncTask : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FLeaderboardFindTaskResult Success;
    UPROPERTY(BlueprintAssignable)
    FLeaderboardFindTaskResult Failed;
    UPROPERTY(BlueprintAssignable, meta = (DisplayName = "IO Error"))
    FLeaderboardFindTaskResult IOError;

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Find Leaderboard - Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|User Stats")
    static UFindLeaderboardAsyncTask* SteamFindLeaderboard(FString apiName);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Find or Create Leaderboard - Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|User Stats")
    static UFindLeaderboardAsyncTask* SteamFindOrCreateLeaderboard(FString apiName, UELeaderboardSortMethod sortMethod, UELeaderboardDisplayType displayType);

    void Activate() override;

private:
    CCallResult<UFindLeaderboardAsyncTask, LeaderboardFindResult_t> m_LeaderboardFindResult_t;
    // ReSharper disable once CppUE4ProbableMemoryIssuesWithUObject
    UObject* WorldContextObject;
    FString ApiName;
    bool CreateIfMissing;
    UELeaderboardSortMethod SortMethod;
    UELeaderboardDisplayType DisplayType;

    void HandleFind(LeaderboardFindResult_t* Response, bool bIOError);
};