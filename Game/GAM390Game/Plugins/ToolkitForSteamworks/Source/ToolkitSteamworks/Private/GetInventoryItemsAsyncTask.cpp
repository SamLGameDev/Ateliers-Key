/**************************************************************************************
*                                                                                     *
* Copyright   2023-2025 by Heathen Engineering Limited, an Irish registered company   *
* # 556277, VAT IE3394133CH, contact Heathen via support@heathen.group                *
*                                                                                     *
***************************************************************************************/


#include "GetInventoryItemsAsyncTask.h"

UGetInventoryItemsAsyncTask* UGetInventoryItemsAsyncTask::SteamGetAllItems(UObject* WorldContextObject)
{
    UGetInventoryItemsAsyncTask* Node = NewObject<UGetInventoryItemsAsyncTask>();    

    Node->Request = FItemResultRequest();
    Node->Request.clearAll = true;
    Node->Request.properties = TArray<FString>();
    Node->Request.callback.BindUFunction(Node, FName("SteamCallback"));
    Node->Mode = 0;

    return Node;
}

UGetInventoryItemsAsyncTask* UGetInventoryItemsAsyncTask::SteamGrantPromoItems(UObject* WorldContextObject)
{
    UGetInventoryItemsAsyncTask* Node = NewObject<UGetInventoryItemsAsyncTask>();

    Node->Request = FItemResultRequest();
    Node->Request.clearAll = false;
    Node->Request.properties = TArray<FString>();
    Node->Request.callback.BindUFunction(Node, FName("SteamCallback"));
    Node->Mode = 1;

    return Node;
}

UGetInventoryItemsAsyncTask* UGetInventoryItemsAsyncTask::SteamAddPromoItem(UObject* WorldContextObject, int32 itemDef)
{
    UGetInventoryItemsAsyncTask* Node = NewObject<UGetInventoryItemsAsyncTask>();

    Node->Request = FItemResultRequest();
    Node->Request.clearAll = false;
    Node->Request.properties = TArray<FString>();
    Node->Request.callback.BindUFunction(Node, FName("SteamCallback"));
    Node->Mode = 2;
    Node->ItemDef = itemDef;

    return Node;
}

UGetInventoryItemsAsyncTask* UGetInventoryItemsAsyncTask::SteamAddPromoItemProperties(UObject* WorldContextObject, int32 itemDef, TArray<FString> readProperties)
{
    UGetInventoryItemsAsyncTask* Node = NewObject<UGetInventoryItemsAsyncTask>();

    Node->Request = FItemResultRequest();
    Node->Request.clearAll = false;
    Node->Request.properties = readProperties;
    Node->Request.callback.BindUFunction(Node, FName("SteamCallback"));
    Node->Mode = 2;
    Node->ItemDef = itemDef;

    return Node;
}

UGetInventoryItemsAsyncTask* UGetInventoryItemsAsyncTask::SteamAddPromoItems(UObject* WorldContextObject, TArray<int32> itemDefs)
{
    UGetInventoryItemsAsyncTask* Node = NewObject<UGetInventoryItemsAsyncTask>();

    Node->Request = FItemResultRequest();
    Node->Request.clearAll = false;
    Node->Request.properties = TArray<FString>();
    Node->Request.callback.BindUFunction(Node, FName("SteamCallback"));
    Node->Mode = 3;
    Node->ItemDefs = itemDefs;

    return Node;
}

UGetInventoryItemsAsyncTask* UGetInventoryItemsAsyncTask::SteamAddPromoItemsProperties(UObject* WorldContextObject, TArray<int32> itemDefs, TArray<FString> readProperties)
{
    UGetInventoryItemsAsyncTask* Node = NewObject<UGetInventoryItemsAsyncTask>();

    Node->Request = FItemResultRequest();
    Node->Request.clearAll = false;
    Node->Request.properties = readProperties;
    Node->Request.callback.BindUFunction(Node, FName("SteamCallback"));
    Node->Mode = 3;
    Node->ItemDefs = itemDefs;

    return Node;
}

UGetInventoryItemsAsyncTask* UGetInventoryItemsAsyncTask::SteamConsumeItem(UObject* WorldContextObject, int64 itemInstanceId, int32 quantity)
{
    UGetInventoryItemsAsyncTask* Node = NewObject<UGetInventoryItemsAsyncTask>();

    Node->Request = FItemResultRequest();
    Node->Request.clearAll = false;
    Node->Request.properties = TArray<FString>();
    Node->Request.callback.BindUFunction(Node, FName("SteamCallback"));
    Node->Mode = 4;
    Node->ItemInstanceId = itemInstanceId;
    Node->Quantity = quantity;

    return Node;
}

UGetInventoryItemsAsyncTask* UGetInventoryItemsAsyncTask::SteamExchangeItem(UObject* WorldContextObject, int32 itemDef, TArray<FItemCount> recipe)
{
    UGetInventoryItemsAsyncTask* Node = NewObject<UGetInventoryItemsAsyncTask>();

    Node->Request = FItemResultRequest();
    Node->Request.clearAll = false;
    Node->Request.properties = TArray<FString>();
    Node->Request.callback.BindUFunction(Node, FName("SteamCallback"));
    Node->Mode = 5;
    Node->ItemDef = itemDef;
    Node->Recipe = recipe;

    return Node;
}

UGetInventoryItemsAsyncTask* UGetInventoryItemsAsyncTask::SteamExchangeItemProperties(UObject* WorldContextObject, int32 itemDef, TArray<FItemCount> recipe, TArray<FString> readProperties)
{
    UGetInventoryItemsAsyncTask* Node = NewObject<UGetInventoryItemsAsyncTask>();

    Node->Request = FItemResultRequest();
    Node->Request.clearAll = false;
    Node->Request.properties = readProperties;
    Node->Request.callback.BindUFunction(Node, FName("SteamCallback"));
    Node->Mode = 5;
    Node->ItemDef = itemDef;
    Node->Recipe = recipe;

    return Node;
}

UGetInventoryItemsAsyncTask* UGetInventoryItemsAsyncTask::SteamGenerateItem(UObject* WorldContextObject, TArray<FItemTypeCount> items)
{
    UGetInventoryItemsAsyncTask* Node = NewObject<UGetInventoryItemsAsyncTask>();

    Node->Request = FItemResultRequest();
    Node->Request.clearAll = false;
    Node->Request.properties = TArray<FString>();
    Node->Request.callback.BindUFunction(Node, FName("SteamCallback"));
    Node->Mode = 5;
    Node->Items = items;

    return Node;
}

UGetInventoryItemsAsyncTask* UGetInventoryItemsAsyncTask::SteamGenerateItemProperties(UObject* WorldContextObject, TArray<FItemTypeCount> items, TArray<FString> readProperties)
{
    UGetInventoryItemsAsyncTask* Node = NewObject<UGetInventoryItemsAsyncTask>();

    Node->Request = FItemResultRequest();
    Node->Request.clearAll = false;
    Node->Request.properties = readProperties;
    Node->Request.callback.BindUFunction(Node, FName("SteamCallback"));
    Node->Mode = 5;
    Node->Items = items;

    return Node;
}

void UGetInventoryItemsAsyncTask::Activate()
{
    USteamToolsSubsystem* SteamGameInstance = GEngine->GetWorld()->GetGameInstance()->GetSubsystem<USteamToolsSubsystem>();
    SteamItemInstanceID_t steamItemInstanceId = SteamItemInstanceID_t(ItemInstanceId);
    TArray<SteamItemDef_t> steamItemDefs;
    TArray<uint32> generateQuantities;
    generateQuantities.Add(1);
    TArray<SteamItemInstanceID_t> destroyItems;
    TArray<uint32> destroyQuantities;

    

    if (!SteamGameInstance)
    {
        UE_LOG(LogTemp, Warning, TEXT("SteamGameInstance is not available"));
        Completed.Broadcast(UEResult::EPC_IOFailure, TArray<FItemDetailWithProperties>());
    }
    else if (SteamAPI_Init())
    {
        switch (Mode)
        {
            case 0: //Get All
                SteamInventoryResult_t handle;
                if (SteamInventory()->GetAllItems(&handle))
                {
                    SteamGameInstance->InventoryRequests.Add(handle, Request);
                }
                else
                {
                    Completed.Broadcast(UEResult::EPC_IOFailure, TArray<FItemDetailWithProperties>());
                }
            break;
            case 1: //Generate Promo
                if (SteamInventory()->GrantPromoItems(&handle))
                {
                    SteamGameInstance->InventoryRequests.Add(handle, Request);
                }
                else
                {
                    Completed.Broadcast(UEResult::EPC_IOFailure, TArray<FItemDetailWithProperties>());
                }
                break;
            case 2: // Add Promo Item
                if (SteamInventory()->AddPromoItem(&handle, SteamItemDef_t(ItemDef)))
                {
                    SteamGameInstance->InventoryRequests.Add(handle, Request);
                }
                else
                {
                    Completed.Broadcast(UEResult::EPC_IOFailure, TArray<FItemDetailWithProperties>());
                }
                break;
            case 3: // Add Promo Items
                for (const int32& itemDef : ItemDefs)
                {
                    steamItemDefs.Add(static_cast<SteamItemDef_t>(itemDef));
                }

                if (SteamInventory()->AddPromoItems(&handle, steamItemDefs.GetData(), steamItemDefs.Num()))
                {
                    SteamGameInstance->InventoryRequests.Add(handle, Request);
                }
                else
                {
                    Completed.Broadcast(UEResult::EPC_IOFailure, TArray<FItemDetailWithProperties>());
                }
                break;
            case 4: // Consume Item
                

                if (SteamInventory()->ConsumeItem(&handle, steamItemInstanceId, static_cast<uint32>(Quantity)))
                {
                    SteamGameInstance->InventoryRequests.Add(handle, Request);
                }
                else
                {
                    Completed.Broadcast(UEResult::EPC_IOFailure, TArray<FItemDetailWithProperties>());
                }
                break;
            case 5: // Exchange Items
                steamItemDefs.Add(SteamItemDef_t(ItemDef));
                for (const FItemCount& item : Recipe)
                {
                    destroyItems.Add(static_cast<SteamItemInstanceID_t>(item.InstanceId));
                    destroyQuantities.Add(static_cast<uint32>(item.Quantity));
                }

                if (SteamInventory()->ExchangeItems(&handle,
                    steamItemDefs.GetData(), generateQuantities.GetData(), steamItemDefs.Num(),
                    destroyItems.GetData(), destroyQuantities.GetData(), destroyItems.Num()))
                {
                    SteamGameInstance->InventoryRequests.Add(handle, Request);
                }
                else
                {
                    Completed.Broadcast(UEResult::EPC_IOFailure, TArray<FItemDetailWithProperties>());
                }
                break;
            case 6: // Generate Items
                for (const FItemTypeCount& item : Items)
                {
                    steamItemDefs.Add(static_cast<SteamItemDef_t>(item.DefinitionId));
                    generateQuantities.Add(static_cast<uint32>(item.Quantity));
                }

                if (SteamInventory()->GenerateItems(&handle, steamItemDefs.GetData(), generateQuantities.GetData(), steamItemDefs.Num()))
                {
                    SteamGameInstance->InventoryRequests.Add(handle, Request);
                }
                else
                {
                    Completed.Broadcast(UEResult::EPC_IOFailure, TArray<FItemDetailWithProperties>());
                }
                break;
        }
    }
    else
    {
        Completed.Broadcast(UEResult::EPC_IOFailure, TArray<FItemDetailWithProperties>());
    }
}

void UGetInventoryItemsAsyncTask::SteamCallback(UEResult Result, const TArray<FItemDetailWithProperties>& ResultItems)
{
    Completed.Broadcast(Result, ResultItems);
    SetReadyToDestroy();
}
