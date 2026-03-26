// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GAM390GameEditorTarget : TargetRules
{
	public GAM390GameEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
        ExtraModuleNames.AddRange(new string[] { "GAM390Game", "ProcEnemies", "GeneralUtilities", "VariableStores", "DamageSystem", "UserSettings", "LevelManagers", "Subtitles", "Menus", "Hacking", "SoundManagement", "TimeManagementExtended" });
        RegisterModulesCreatedByRider();
	}

	private void RegisterModulesCreatedByRider()
	{
		ExtraModuleNames.AddRange(new string[] { "AbilitySystem", "AI", "HeatMap", "HeatMapEditor", "QuestSystem", "DisplayControlsSystem", "NotifySystem" });
	}
}
