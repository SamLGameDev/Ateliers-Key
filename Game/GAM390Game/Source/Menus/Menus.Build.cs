// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Menus : ModuleRules
{
	public Menus(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "UserSettings", "LevelManagers", "GeneralUtilities", "Subtitles", "UMG", "Slate", "SlateCore", "SoundManagement", "EnhancedInput"});
	}
}
