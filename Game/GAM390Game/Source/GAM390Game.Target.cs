// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GAM390GameTarget : TargetRules
{
	public GAM390GameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.AddRange(new string[] { "GAM390Game", "ProcEnemies", "GeneralUtilities", "VariableStores", "DamageSystem", "UserSettings", "LevelManagers", "Subtitles", "Menus" });
	}
}
