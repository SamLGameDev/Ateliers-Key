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
#include "GetWebAuthTicketAsyncTask.generated.h"

UCLASS()
class TOOLKITSTEAMWORKS_API UGetWebAuthTicketAsyncTask : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FGetTicketForWebApiResponseCallback Completed;

	UFUNCTION()
	void SteamCallback(UEResult Result, int32 Ticket, TArray<uint8> Data);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Authentication Ticket for Web API - Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|Inventory")
	static UGetWebAuthTicketAsyncTask* SteamGetWebAuthTicket(FString Identity, UObject* WorldContextObject);

	void Activate() override;

private:
	FString _Identity;
};