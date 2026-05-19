/**************************************************************************************
*                                                                                     *
* Copyright   2023-2025 by Heathen Engineering Limited, an Irish registered company   *
* # 556277, VAT IE3394133CH, contact Heathen via support@heathen.group                *
*                                                                                     *
***************************************************************************************/
#include "AchievementDataAsset.h"

FString UAchievementDataAsset::GetDisplayName() const
{
	STEAM_CLIENT(FString());
	FString name = FString(SteamUserStats()->GetAchievementDisplayAttribute(StringCast<ANSICHAR>(*ApiName).Get(), "name"));
	return name;
}

FString UAchievementDataAsset::GetDescription() const
{
	STEAM_CLIENT(FString());
	FString desc = FString(SteamUserStats()->GetAchievementDisplayAttribute(StringCast<ANSICHAR>(*ApiName).Get(), "desc"));
	return desc;
}

bool UAchievementDataAsset::GetIsHidden() const
{
	STEAM_CLIENT(false);
	const char* DisplayAttribute = SteamUserStats()->GetAchievementDisplayAttribute(StringCast<ANSICHAR>(*ApiName).Get(), "hidden");
	bool isHidden = (DisplayAttribute && strcmp(DisplayAttribute, "1") == 0);
	return isHidden;
}

bool UAchievementDataAsset::GetIsAchieved() const
{
	STEAM_CLIENT(false);
	bool achieved;
	SteamUserStats()->GetAchievement(StringCast<ANSICHAR>(*ApiName).Get(), &achieved);
	return achieved;
}

bool UAchievementDataAsset::SetIsAchieved(bool bNewValue) const
{
	STEAM_CLIENT(false);

	if(bNewValue)	
		return SteamUserStats()->SetAchievement(StringCast<ANSICHAR>(*ApiName).Get());
	else
		return SteamUserStats()->ClearAchievement(StringCast<ANSICHAR>(*ApiName).Get());
}

FDateTime UAchievementDataAsset::GetUnlockTime() const
{
	STEAM_CLIENT(FDateTime());
	bool achieved;
	uint32 unixTime;
	SteamUserStats()->GetAchievementAndUnlockTime(StringCast<ANSICHAR>(*ApiName).Get(), &achieved, &unixTime);
	return FDateTime::FromUnixTimestamp(static_cast<int64>(unixTime));
}

float UAchievementDataAsset::GetGlobalPercent() const
{
	STEAM_CLIENT(0.0f);
	float pert;
	SteamUserStats()->GetAchievementAchievedPercent(StringCast<ANSICHAR>(*ApiName).Get(), &pert);
	return pert;
}

FAchievementStatus UAchievementDataAsset::GetStatus() const
{
	STEAM_CLIENT(FAchievementStatus());

	auto AnsiName = StringCast<ANSICHAR>(*ApiName);
	const char* Name = AnsiName.Get();

	bool achieved = false;
	uint32 unixTime = 0;
	float percent = 0.0f;

	SteamUserStats()->GetAchievementAndUnlockTime(Name, &achieved, &unixTime);
	SteamUserStats()->GetAchievementAchievedPercent(Name, &percent);

	FString displayName = FString(SteamUserStats()->GetAchievementDisplayAttribute(Name, "name"));
	FString description = FString(SteamUserStats()->GetAchievementDisplayAttribute(Name, "desc"));

	const char* hiddenAttr = SteamUserStats()->GetAchievementDisplayAttribute(Name, "hidden");
	bool isHidden = (hiddenAttr && strcmp(hiddenAttr, "1") == 0);

	FAchievementStatus status;
	status.bAchieved = achieved;
	status.Percent = percent;
	status.UnlockTime = FDateTime::FromUnixTimestamp(static_cast<int64>(unixTime));
	status.Name = displayName;
	status.Description = description;
	status.bIsHidden = isHidden;

	return status;
}

FUserAchievementStatus UAchievementDataAsset::GetStatusForUser(int64 user) const
{
	STEAM_CLIENT(FUserAchievementStatus());
	CSteamID steamId = INT64_TO_STEAMID(user);

	bool achieved;
	uint32 unixTime;
	SteamUserStats()->GetUserAchievementAndUnlockTime(steamId, StringCast<ANSICHAR>(*ApiName).Get(), &achieved, &unixTime);

	FUserAchievementStatus status;
	status.bAchieved = achieved;
	status.UnlockTime = FDateTime::FromUnixTimestamp(static_cast<int64>(unixTime));

	return status;
}

void UAchievementDataAsset::GetIcon(FIconLoadCallback callback) const
{
	STEAM_CLIENT_INSTANCE(;);
	int32 handle = SteamUserStats()->GetAchievementIcon(StringCast<ANSICHAR>(*ApiName).Get());

	if (handle > 0)
		SteamToolsSubsystem->LoadIcon(handle, ApiName, callback);
	else
	{
		if (SteamToolsSubsystem->AchievementIconRequests.Contains(ApiName))
			SteamToolsSubsystem->AchievementIconRequests.Remove(ApiName);

		SteamToolsSubsystem->AchievementIconRequests.Add(ApiName, callback);
	}
}
