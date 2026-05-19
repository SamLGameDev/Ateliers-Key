// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GAM390GameTarget : TargetRules
{
	public GAM390GameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
		
		ProjectDefinitions.Add("UE_PROJECT_STEAMSHIPPINGID=4759400");
		ProjectDefinitions.Add("UE_PROJECT_STEAMGAMEDESC=Atelier's Key");
		ProjectDefinitions.Add("UE_PROJECT_STEAMGAMEDIR=AteliersKey");
		ProjectDefinitions.Add("UE_PROJECT_STEAMPRODUCTNAME=4759400");
		
		ExtraModuleNames.AddRange(new string[] { "GAM390Game", "ProcEnemies", "GeneralUtilities", "VariableStores", "DamageSystem", "UserSettings", "LevelManagers", "Subtitles", "Menus", "Hacking", "SoundManagement", "TimeManagementExtended" });
		RegisterModulesCreatedByRider();
	}

	private void RegisterModulesCreatedByRider()
	{
		ExtraModuleNames.AddRange(new string[] {"AbilitySystem", "AI", "HeatMap", "QuestSystem", "DisplayControlsSystem", "NotifySystem", "PoolingSystem" });
	}
}
