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
#include "BeginAuthSessionAsyncTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBeginAuthSessionTaskDelegate, FAuthenticationSession, Session);

UCLASS()
class TOOLKITSTEAMWORKS_API UBeginAuthSessionAsyncTask : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FBeginAuthSessionTaskDelegate Completed;

	UFUNCTION()
	void SteamCallback(const int64 User, const int64 Owner, const UEAuthSessionResponse Response);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Begin Auth Session - Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|User")
	static UBeginAuthSessionAsyncTask* SteamBeginAuthSessionUser(TArray<uint8> Ticket, int64 SteamId, UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Begin Auth Session - Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|Steam Game Server")
	static UBeginAuthSessionAsyncTask* SteamBeginAuthSessionServer(TArray<uint8> Ticket, int64 SteamId, UObject* WorldContextObject);

	void Activate() override;

private:
	FAuthenticationSession Request = FAuthenticationSession();
};