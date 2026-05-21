// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LevelManagers : ModuleRules
{
	public LevelManagers(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "LevelSequence"});
	}
}
