// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Subtitles : ModuleRules
{
	public Subtitles(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "UserSettings", "UMG", "Slate", "SlateCore"});
	}
}
