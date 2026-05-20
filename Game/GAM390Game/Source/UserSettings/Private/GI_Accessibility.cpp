
// Fill out your copyright notice in the Description page of Project Settings.
#include "GI_Accessibility.h"

#include "UBaseGameUserSettings.h"
#include "SettingsSave.h"
#include "Kismet/GameplayStatics.h"

#define DISCORD_APPLICATION_ID 1506692667524907119

void UGI_SanctumSettings::Init()
{
	Super::Init();

	SyncSubtitlesSettings();

	UE_LOG(LogTemp, Log, TEXT("GameInstance Init - Starting Discord setup"));

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&UGI_SanctumSettings::SyncSubtitlesSettings,
		1.0f,
		false
	);

	FTimerHandle DiscordTimer;
	GetWorld()->GetTimerManager().SetTimer(
		DiscordTimer,
		[this]()
		{
			APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (!PC)
			{
				UE_LOG(LogTemp, Warning, TEXT("Discord init failed: No PlayerController"));
				return;
			}

			ULocalPlayer* LP = PC->GetLocalPlayer();
			if (!LP)
			{
				UE_LOG(LogTemp, Warning, TEXT("Discord init failed: No LocalPlayer"));
				return;
			}

			Discord = ULocalPlayer::GetSubsystem<UDiscordLocalPlayerSubsystem>(LP);

			if (!Discord)
			{
				UE_LOG(LogTemp, Warning, TEXT("Discord subsystem not available"));
				return;
			}

			if (!Discord->Client)
			{
				UE_LOG(LogTemp, Warning, TEXT("Discord Client is null"));
				return;
			}

			UE_LOG(LogTemp, Log, TEXT("Connecting to Discord..."));

 			auto LogCallback = FDiscordClientLogCallback::CreateUObject(
				 this, &UGI_SanctumSettings::OnDiscordLogMessage
 			);
 			Discord->Client->AddLogCallback(LogCallback, EDiscordLoggingSeverity::Info);
 			
 			FScriptDelegate StatusChanged;
 			StatusChanged.BindUFunction(this, FName("OnDiscordStatusChanged"));
 			Discord->OnStatusChanged.Add(StatusChanged);
 			
 			CodeVerifier = Discord->Client->CreateAuthorizationCodeVerifier();
 			
 			UDiscordAuthorizationArgs* AuthArgs = NewObject<UDiscordAuthorizationArgs>();
 			AuthArgs->Init();
 			AuthArgs->SetClientId(DISCORD_APPLICATION_ID);
 			AuthArgs->SetScopes(UDiscordClient::GetDefaultPresenceScopes());
 			AuthArgs->SetCodeChallenge(CodeVerifier->Challenge());
 			
 			DiscordConnect();
		},
		1.5f,
		false
	);
}

void UGI_SanctumSettings::DiscordConnect()
{
	// Try to load a saved token first
	USettingsSave* Save = Cast<USettingsSave>(
		UGameplayStatics::LoadGameFromSlot("settings", 0)
	);

	if (Save && !Save->DiscordAccessToken.IsEmpty())
	{
		UE_LOG(LogTemp, Log, TEXT("Discord: found saved token, skipping auth..."));

		Discord->Client->UpdateToken(
				Save->DiscordTokenType,
				Save->DiscordAccessToken,
				FDiscordClientUpdateTokenCallback::CreateUObject(
				this, &UGI_SanctumSettings::OnDiscordTokenUpdated
			)
		);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Discord: no saved token, starting auth flow..."));

		CodeVerifier = Discord->Client->CreateAuthorizationCodeVerifier();

		UDiscordAuthorizationArgs* AuthArgs = NewObject<UDiscordAuthorizationArgs>();
		AuthArgs->Init();
		AuthArgs->SetClientId(DISCORD_APPLICATION_ID);
		AuthArgs->SetScopes(UDiscordClient::GetDefaultPresenceScopes());
		AuthArgs->SetCodeChallenge(CodeVerifier->Challenge());

		Discord->Client->Authorize(
			AuthArgs,
			FDiscordClientAuthorizationCallback::CreateUObject(
				this, &UGI_SanctumSettings::OnDiscordAuthorizeCompleted
			)
		);
	}
}

void UGI_SanctumSettings::OnDiscordTokenExchange(
	UDiscordClientResult* Result, FString AccessToken, FString RefreshToken,
	EDiscordAuthorizationTokenType TokenType, int32 ExpiresIn, FString Scope)
{
	if (!Result->Successful())
	{
		UE_LOG(LogTemp, Error, TEXT("Discord token exchange failed: %s"), *Result->Error());
		return;
	}

	// Save the token so we skip auth next launch
	USettingsSave* Save = Cast<USettingsSave>(
		UGameplayStatics::LoadGameFromSlot("settings", 0)
	);
	if (!Save)
	{
		Save = Cast<USettingsSave>(
			UGameplayStatics::CreateSaveGameObject(USettingsSave::StaticClass())
		);
	}

	Save->DiscordAccessToken = AccessToken;
	Save->DiscordRefreshToken = RefreshToken;
	Save->DiscordTokenType = TokenType;
	UGameplayStatics::AsyncSaveGameToSlot(Save, "settings", 0);

	UE_LOG(LogTemp, Log, TEXT("Discord token saved"));

	Discord->Client->UpdateToken(
		TokenType,
		AccessToken,
		FDiscordClientUpdateTokenCallback::CreateUObject(
			this, &UGI_SanctumSettings::OnDiscordTokenUpdated
		)
	);
}

void UGI_SanctumSettings::OnDiscordLogMessage(FString Message, EDiscordLoggingSeverity Severity)
{
	UE_LOG(LogTemp, Log, TEXT("[Discord][%s] %s"),
		*UEnum::GetValueAsString(Severity), *Message);
}

void UGI_SanctumSettings::OnDiscordAuthorizeCompleted(
	UDiscordClientResult* Result, FString Code, FString RedirectUri)
{
	if (!Result->Successful())
	{
		UE_LOG(LogTemp, Error, TEXT("Discord authorization failed: %s"), *Result->Error());
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Discord authorization successful, exchanging token..."));

	Discord->Client->GetToken(
		DISCORD_APPLICATION_ID,
		Code,
		CodeVerifier->Verifier(),
		RedirectUri,
		FDiscordClientTokenExchangeCallback::CreateUObject(
			this, &UGI_SanctumSettings::OnDiscordTokenExchange
		)
	);
}

void UGI_SanctumSettings::OnDiscordTokenUpdated(UDiscordClientResult* Result)
{
	if (!Result->Successful())
	{
		UE_LOG(LogTemp, Error, TEXT("Discord token update failed: %s"), *Result->Error());
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Discord token updated, connecting..."));
	Discord->Client->Connect();
}

void UGI_SanctumSettings::SetDiscordPresence(FString State, FString Details)
{
	if (!Discord || !Discord->Client)
	{
		UE_LOG(LogTemp, Warning, TEXT("Discord not initialised"));
		return;
	}

	if (Discord->Client->GetStatus() != EDiscordClientStatus::Ready)
	{
		UE_LOG(LogTemp, Warning, TEXT("Discord not ready yet"));
		return;
	}

	UDiscordActivity* Activity = NewObject<UDiscordActivity>();
	Activity->Init();
	Activity->SetType(EDiscordActivityTypes::Playing);
	Activity->SetState(TCHAR_TO_UTF8(*State));
	Activity->SetDetails(TCHAR_TO_UTF8(*Details));

	Discord->Client->UpdateRichPresence(
		Activity,
		nullptr
	);

	UE_LOG(LogTemp, Log, TEXT("Discord Presence Updated: %s | %s"), *State, *Details);
}

void UGI_SanctumSettings::SetDiscordPresenceDetailsOnly(FString Details)
{
	if (!Discord || !Discord->Client)
	{
		UE_LOG(LogTemp, Warning, TEXT("Discord not initialised"));
		return;
	}

	if (Discord->Client->GetStatus() != EDiscordClientStatus::Ready)
	{
		UE_LOG(LogTemp, Warning, TEXT("Discord not ready yet"));
		return;
	}

	UDiscordActivity* Activity = NewObject<UDiscordActivity>();
	Activity->Init();
	Activity->SetType(EDiscordActivityTypes::Playing);
	Activity->SetDetails(TCHAR_TO_UTF8(*Details));

	Discord->Client->UpdateRichPresence(
		Activity,
		nullptr
	);

	UE_LOG(LogTemp, Log, TEXT("Discord Presence Updated: %s"), *Details);
}


void UGI_SanctumSettings::OnDiscordStatusChanged(
	EDiscordClientStatus Status,
	EDiscordClientError Error,
	int32 ErrorDetail)
{
	UE_LOG(LogTemp, Log, TEXT("Discord Status: %s"),
		*UEnum::GetValueAsString(Status));

	if (Status == EDiscordClientStatus::Ready)
	{
		UE_LOG(LogTemp, Log, TEXT("Discord READY"));
		SetDiscordPresenceDetailsOnly(TEXT("In Main Menu"));
	}
	else if (Error != EDiscordClientError::None)
	{
		UE_LOG(LogTemp, Error, TEXT("Discord Error: %s (%d)"),
			*UEnum::GetValueAsString(Error), ErrorDetail);
	}
}

void UGI_SanctumSettings::SyncSubtitlesSettings()
{
	UUBaseGameUserSettings* gameUserSettings = Cast<UUBaseGameUserSettings>(UGameUserSettings::GetGameUserSettings());

	if (gameUserSettings)
	{
		bSubtitlesEnabled = gameUserSettings->bSubtitlesEnabled;
		m_Brightness = gameUserSettings->m_Brightness;
		CameraSensitivity = gameUserSettings->CameraSensitivity;
		CameraFov = gameUserSettings->CameraFov;

		if (CameraFov == 0)
		{
			CameraFov = 1;
		}
	}

	if (!UGameplayStatics::DoesSaveGameExist("settings", 0))
	{
		USettingsSave* SaveGame = Cast<USettingsSave>(UGameplayStatics::CreateSaveGameObject(USettingsSave::StaticClass()));
		UGameplayStatics::AsyncSaveGameToSlot(SaveGame, "settings", 0);
	}
}

