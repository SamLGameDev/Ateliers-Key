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
#include "GetInventoryItemsAsyncTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemResultsTaskDelegate, UEResult, result, const TArray<FItemDetailWithProperties>&, items);

UCLASS()
class TOOLKITSTEAMWORKS_API UGetInventoryItemsAsyncTask : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FItemResultsTaskDelegate Completed;

	UFUNCTION()
	void SteamCallback(UEResult Result, const TArray<FItemDetailWithProperties>& ResultItems);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get All Items - Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|Inventory")
	static UGetInventoryItemsAsyncTask* SteamGetAllItems(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Grant Promo Items - Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|Inventory")
	static UGetInventoryItemsAsyncTask* SteamGrantPromoItems(UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Promo Item - Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|Inventory")
	static UGetInventoryItemsAsyncTask* SteamAddPromoItem(UObject* WorldContextObject, int32 itemDef);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Promo Item - Properties Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|Inventory")
	static UGetInventoryItemsAsyncTask* SteamAddPromoItemProperties(UObject* WorldContextObject, int32 itemDef, TArray<FString> readProperties);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Promo Items - Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|Inventory")
	static UGetInventoryItemsAsyncTask* SteamAddPromoItems(UObject* WorldContextObject, TArray<int32> itemDefs);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Promo Items - Properties Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|Inventory")
	static UGetInventoryItemsAsyncTask* SteamAddPromoItemsProperties(UObject* WorldContextObject, TArray<int32> itemDefs, TArray<FString> readProperties);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Consume Item - Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|Inventory")
	static UGetInventoryItemsAsyncTask* SteamConsumeItem(UObject* WorldContextObject, int64 itemInstanceId, int32 quantity);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Exchange Items - Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|Inventory")
	static UGetInventoryItemsAsyncTask* SteamExchangeItem(UObject* WorldContextObject, int32 itemDef, TArray<FItemCount> recipe);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Exchange Items - Properties Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|Inventory")
	static UGetInventoryItemsAsyncTask* SteamExchangeItemProperties(UObject* WorldContextObject, int32 itemDef, TArray<FItemCount> recipe, TArray<FString> readProperties);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Generate Item - Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|Inventory")
	static UGetInventoryItemsAsyncTask* SteamGenerateItem(UObject* WorldContextObject, TArray<FItemTypeCount> items);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Generate Item - Properties Task", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Heathen's Toolkit|Steamworks|Inventory")
	static UGetInventoryItemsAsyncTask* SteamGenerateItemProperties(UObject* WorldContextObject, TArray<FItemTypeCount> items, TArray<FString> readProperties);

	void Activate() override;

private:
	int Mode = 0;
	int32 ItemDef;
	TArray<int32> ItemDefs;
	int64 ItemInstanceId;
	int32 Quantity;
	TArray<FItemCount> Recipe;
	TArray<FItemTypeCount> Items;
	FItemResultRequest Request = FItemResultRequest();
};