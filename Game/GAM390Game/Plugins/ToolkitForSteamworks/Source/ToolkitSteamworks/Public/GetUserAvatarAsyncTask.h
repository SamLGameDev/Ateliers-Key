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
#include "GetUserAvatarAsyncTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAvatarLoadTaskDelegate, UTexture2D*, Avatar);

UCLASS()
class TOOLKITSTEAMWORKS_API UGetUserAvatarAsyncTask : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FAvatarLoadTaskDelegate Success;
	UPROPERTY(BlueprintAssignable)
	FAvatarLoadTaskDelegate Failed;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Avatar - Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|Friends")
	static UGetUserAvatarAsyncTask* SteamGetAvatar(UObject* WorldContextObject, int64 UserId);

	UFUNCTION()
	void HandleAvatarLoad(UTexture2D* Avatar);

	void Activate() override;

private:
	UObject* WorldContextObject;
	CSteamID UserId;
};