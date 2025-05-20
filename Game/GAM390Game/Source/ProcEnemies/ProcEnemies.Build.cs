// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProcEnemies : ModuleRules
{
	public ProcEnemies(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "GeneralUtilities", "VariableStores"});
	}
}
