// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GeneralUtilities : ModuleRules
{
	public GeneralUtilities(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "UMG" });
	}
}
