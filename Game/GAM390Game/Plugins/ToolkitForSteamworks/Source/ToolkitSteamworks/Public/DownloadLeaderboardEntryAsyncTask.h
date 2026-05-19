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
#include "DownloadLeaderboardEntryAsyncTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLeaderboardEntriesDownloadedTaskResult, const TArray<FLeaderboardEntry>&, Results);

UCLASS()
class TOOLKITSTEAMWORKS_API UDownloadLeaderboardEntryAsyncTask : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
        FLeaderboardEntriesDownloadedTaskResult Complete;
    UPROPERTY(BlueprintAssignable, meta = (DisplayName = "IO Error"))
        FLeaderboardEntriesDownloadedTaskResult IOError;

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Download Leaderboard Entries - Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|User Stats")
        static UDownloadLeaderboardEntryAsyncTask* SteamDownloadLeaderboardEntries(int64 boardId, UELeaderboardDataRequest requestType, int32 start, int32 end, int32 detailCount);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Download Leaderboard Entries for Users - Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|User Stats")
        static UDownloadLeaderboardEntryAsyncTask* SteamDownloadLeaderboardEntriesForUsers(int64 boardId, TArray<int64> users, int32 detailCount);

    void Activate() override;

private:
    CCallResult<UDownloadLeaderboardEntryAsyncTask, LeaderboardScoresDownloaded_t> m_LeaderboardScoresDownloaded_t;
    // ReSharper disable once CppUE4ProbableMemoryIssuesWithUObject
    UObject* WorldContextObject;
    bool ForUsers;
    SteamLeaderboard_t Board;
    ELeaderboardDataRequest Request;
    int Start;
    int End;
    int DetailCount;
    TArray<CSteamID> Users;

    void HandleResults(LeaderboardScoresDownloaded_t* Response, bool bIOError);
};