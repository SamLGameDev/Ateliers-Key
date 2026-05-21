// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TimeManagementExtended : ModuleRules
{
    public TimeManagementExtended(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine"});
	}
}
