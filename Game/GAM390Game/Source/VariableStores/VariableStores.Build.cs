// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VariableStores : ModuleRules
{
	public VariableStores(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine"});
	}
}
