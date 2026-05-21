// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using UnrealBuildTool.Rules;

public class GAM390Game : ModuleRules
{
	public GAM390Game(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GeneralUtilities", "VariableStores", "ProcEnemies", "DamageSystem", "LevelManagers", "Subtitles", "Menus", "Hacking", "UMG", "Slate", "SlateCore", "SoundManagement", "TimeManagementExtended", "AbilitySystem", "AI", "NavigationSystem", "UserSettings", "QuestSystem", "CommonInput" });

        PrivateDependencyModuleNames.AddRange(new string[] { "DiscordPartnerSDK" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
