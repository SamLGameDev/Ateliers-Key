/**************************************************************************************
*                                                                                     *
* Copyright   2023-2025 by Heathen Engineering Limited, an Irish registered company   *
* # 556277, VAT IE3394133CH, contact Heathen via support@heathen.group                *
*                                                                                     *
***************************************************************************************/


#include "GetUserAvatarAsyncTask.h"

UGetUserAvatarAsyncTask* UGetUserAvatarAsyncTask::SteamGetAvatar(UObject* WorldContextObject, int64 UserId)
{
    UGetUserAvatarAsyncTask* Node = NewObject<UGetUserAvatarAsyncTask>();
    Node->WorldContextObject = WorldContextObject;
    Node->UserId = CSteamID(static_cast<uint64>(UserId));
    return Node;
}

void UGetUserAvatarAsyncTask::HandleAvatarLoad(UTexture2D* Avatar)
{
    if (Avatar)
    {
        UE_LOG(LogTemp, Log, TEXT("Avatar loaded successfully."));
        Success.Broadcast(Avatar);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load avatar."));
        Failed.Broadcast(nullptr);
    }
}

void UGetUserAvatarAsyncTask::Activate()
{
    if (!SteamAPI_Init())
    {
        Failed.Broadcast(nullptr);
        return;
    }

    USteamToolsSubsystem* SteamToolsSubsystem = USteamToolsSubsystem::GetSteamToolsSubsystem();
    if (!SteamToolsSubsystem)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get a valid SteamToolsSubsystem."));
        Failed.Broadcast(nullptr);
        return;
    }

    FAvatarLoadCallback Callback;
    Callback.BindUFunction(this, FName("HandleAvatarLoad"));

    SteamToolsSubsystem->GetAvatarBySteamId(UserId, Callback);
}