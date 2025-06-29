// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UserSettings : ModuleRules
{
	public UserSettings(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "SoundManagement"});
	}
}
