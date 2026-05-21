/**************************************************************************************
*                                                                                     *
* Copyright   2023-2025 by Heathen Engineering Limited, an Irish registered company   *
* # 556277, VAT IE3394133CH, contact Heathen via support@heathen.group                *
*                                                                                     *
***************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/CommandLine.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "Subsystems/GameInstanceSubsystem.h"
THIRD_PARTY_INCLUDES_START
#include <HeathenTools.h>
THIRD_PARTY_INCLUDES_END
#include "SteamToolsSubsystem.generated.h"

/**********************************************
* Defines, common use macros
***********************************************/

DECLARE_DELEGATE_OneParam(SteamGameServerConnectionChangeDelegate, bool);

class FItemResultRequest
{
public:
	/// <summary>
	/// If this request is not for some other user then this flag tells us to clear the data assets and rebuild such as for a Get All
	/// </summary>
	bool clearAll = false;
	/// <summary>
	/// Only used when deserializing inventory results
	/// </summary>
	CSteamID userId;
	/// <summary>
	/// Callback to be executed when the results are finalized
	/// </summary>
	FItemResultsCallback callback;
	/// <summary>
	/// The list of property keys to read for on each item
	/// </summary>
	TArray<FString> properties;
};

//Forward declare the InventoryItemDataAsset type
class UInventoryItemDataAsset;

UCLASS()
class TOOLKITSTEAMWORKS_API USteamToolsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	static uint8 VoiceDataBuffer[8192 * 8];

	virtual void Deinitialize() override
	{
		if (SelfInitalized)
		{
			GetWorld()->GetTimerManager().ClearTimer(SteamCallbackTimerHandle);

			if (GetGameInstance()->IsDedicatedServerInstance())
			{
				SteamGameServer_Shutdown();
				UE_LOG(LogTemp, Log, TEXT("Steam Game Server API has been shutdown"));
			}
			else
			{
				SteamAPI_Shutdown();
				UE_LOG(LogTemp, Log, TEXT("Steam API has been shutdown"));
			}
		}

		Super::Deinitialize();
		UE_LOG(LogTemp, Log, TEXT("SteamToolsSubsystem::Deinitialize"));
	}

	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		Super::Initialize(Collection);
		pInstance = this;
		UE_LOG(LogTemp, Log, TEXT("SteamToolsSubsystem::Initialize"));
	}

	static USteamToolsSubsystem* GetSteamToolsSubsystem()
	{
		return pInstance;
	}

	UFUNCTION(BlueprintCallable, Category = "Steam Game Instance", meta = (WorldContext = "WorldContextObject"))
	FSteamworksInitializationResponse InitializeSteamAPI(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Steam Game Instance")
	void InitializeRelayNetworkAccess();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Clear Inventory Item Details", Keywords = "Heathen Toolkit Steamworks Inventory"), Category = "Steam Game Instance")
	void ClearItemDetails();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Clear Avatar Cash", Keywords = "Heathen Toolkit Steamworks"), Category = "Steam Game Instance")
	void ClearAvatarCash(int64 SteamId);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Clear All Cashed Avatars", Keywords = "Heathen Toolkit Steamworks"), Category = "Steam Game Instance")
	void ClearAllCashedAvatars();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Update Inventory Item Details", Keywords = "Heathen Toolkit Steamworks Inventory"), Category = "Steam Game Instance")
	void UpdateItemDetails(TArray<FItemDetailWithProperties> Details);

	UPROPERTY(EditAnywhere, Category = "General")
	float callbackFrequency = 0.03333f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Inventory Items", Keywords = "Heathen Toolkit Steamworks Inventory"), Category = "General")
	TArray<UInventoryItemDataAsset*> ItemDataAssets;


	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FUserStatsReceived SteamUserStatsReceived;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FUserStatsUnloaded SteamUserStatsUnloaded;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FUserStatsUnloaded SteamUserStatsStored;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FUserAchievementStored SteamUserAchievementStored;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FDlcInstalledEvent SteamDlcInstalled;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FSteamServerConnectFailureCallback SteamServerConnectFailure;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FSteamServersDisconnectedCallback SteamServersDisconnected;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FSteamServersConnectedCallback SteamServersConnected;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FGameConnectedFriendChatMsgCallback SteamFriendChatMsg;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FFriendRichPresenceUpdateCallback SteamFriendRichPresenceUpdate;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FPersonaStateChangeCallback SteamPersonaStateChange;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FGameRichPresenceJoinRequestedCallback SteamRichPresenceJoinRequested;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FGameLobbyJoinRequestedCallback SteamLobbyJoinRequested;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FGameOverlayActivatedCallback SteamGameOverlayActivated;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FGameOverlayActivatedCallbackLegacy SteamGameOverlayActivatedLegacy;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FSteamInventoryResultReadyCallback SteamInventoryResultReady;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FSteamInventoryDefinitionUpdateCallback SteamInventoryDefinitionUpdate;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FMicroTxnAuthorizationResponseCallback SteamMicroTxnAuthorizationResponse;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FFavoritesListAccountsUpdatedCallback SteamFavoritesListAccountsUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FFavoritesListChangedCallback SteamFavoritesListChanged;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FLobbyChatMsgCallback SteamLobbyChatMsg;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FLobbyChatUpdateCallback SteamLobbyChatUpdate;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FLobbyDataUpdateCallback SteamLobbyDataUpdate;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FLobbyEnterCallback SteamLobbyEnter;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FLobbyGameCreatedCallback SteamLobbyGameCreated;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks");
	FLobbyInviteCallback SteamLobbyInvite;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FGetTicketForWebApiResponseCallback SteamTicketForWebApiResponse;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FSteamRemotePlaySessionConnectedCallback SteamRemotePlaySessionConnected;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FSteamRemotePlaySessionDisconnectedCallback SteamRemotePlaySessionDisconnected;

	UPROPERTY(BlueprintAssignable, Category = "Heathen's Toolkit|Steamworks")
	FSteamRemotePlayTogetherGuestInviteCallback SteamRemotePlayTogetherGuestInvite;

	void LoadIcon(int handle, FString apiName, FIconLoadCallback callback);
	void GetAvatarBySteamId(CSteamID SteamId, FAvatarLoadCallback Callback);
	void LoadSteamAvatar(CSteamID SteamId);
	void CopySteamAvatar(int Handle, UTexture2D* AvatarTexture);

	TMap<FString, UTexture2D*> AchievementIcons;
	TMap<FString, FIconLoadCallback> AchievementIconRequests;
	TMap<uint64, UTexture2D*> Avatars;
	TMap<uint64, FAvatarLoadCallback> AvatarRequests;
	TMap<SteamInventoryResult_t, FItemResultRequest> InventoryRequests;
	TMap<uint64, FBeginAuthSessionCallbackDelegate> BeginAuthRequests;
	TMap<int32, FWebApiResponseCallbackDelegate> GetWebAuthRequests;
	UPROPERTY(BlueprintReadOnly, Category = "Heathen's Toolkit|Steamworks", meta = (DisplayName = "Current Lobbies"))
	TArray<int64> MemberOfLobbies;

	SteamGameServerConnectionChangeDelegate SteamGameServerConnectionChanged;

private:
	static USteamToolsSubsystem* pInstance;
	bool SelfInitalized;
	FTimerHandle SteamCallbackTimerHandle;

	STEAM_CALLBACK(USteamToolsSubsystem, EventUserStatsReceived, UserStatsReceived_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventUserStatsUnloaded, UserStatsUnloaded_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventUserStatsStored, UserStatsStored_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventUserAchievementStored, UserAchievementStored_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventUserAchievementIconFetched, UserAchievementIconFetched_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventDlcInstalled, DlcInstalled_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventSteamServerConnectFailure, SteamServerConnectFailure_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventSteamServersConnected, SteamServersConnected_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventSteamServersDisconnected, SteamServersDisconnected_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventGameConnectedFriendChatMsg, GameConnectedFriendChatMsg_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventFriendRichPresenceUpdate, FriendRichPresenceUpdate_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventPersonaStateChange, PersonaStateChange_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventAvatarImageLoaded, AvatarImageLoaded_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventGameRichPresenceJoinRequested, GameRichPresenceJoinRequested_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventGameLobbyJoinRequested, GameLobbyJoinRequested_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventGameOverlayActivated, GameOverlayActivated_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventSteamInventoryResultReady_t, SteamInventoryResultReady_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventSteamInventoryDefinitionUpdate_t, SteamInventoryDefinitionUpdate_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventMicroTxnAuthorizationResponse_t, MicroTxnAuthorizationResponse_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventFavoritesListAccountsUpdated, FavoritesListAccountsUpdated_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventFavoritesListChanged, FavoritesListChanged_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventLobbyChatMsg, LobbyChatMsg_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventLobbyChatUpdate, LobbyChatUpdate_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventLobbyDataUpdate, LobbyDataUpdate_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventLobbyEnter, LobbyEnter_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventLobbyGameCreated, LobbyGameCreated_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventLobbyInvite, LobbyInvite_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventRemotePlaySessionConnected, SteamRemotePlaySessionConnected_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventRemotePlaySessionDisconnected, SteamRemotePlaySessionDisconnected_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventRemotePlaySessionGuestInvite, SteamRemotePlayTogetherGuestInvite_t);
	STEAM_CALLBACK(USteamToolsSubsystem, EventValidateAuthTicket, ValidateAuthTicketResponse_t);

#if STEAM_MAJOR > 1 || (STEAM_MAJOR == 1 && STEAM_MINOR >= 57)
	STEAM_CALLBACK(USteamToolsSubsystem, EventGetTicketForWebApiResponse, GetTicketForWebApiResponse_t);
#endif

	//STEAM_GAMESERVER_CALLBACK
	STEAM_GAMESERVER_CALLBACK(USteamToolsSubsystem, EventSteamGameServerConnectFailure, SteamServerConnectFailure_t);
	STEAM_GAMESERVER_CALLBACK(USteamToolsSubsystem, EventSteamGameServersConnected, SteamServersConnected_t);
	STEAM_GAMESERVER_CALLBACK(USteamToolsSubsystem, EventSteamGameServersDisconnected, SteamServersDisconnected_t);
};
