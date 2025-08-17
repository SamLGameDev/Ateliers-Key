// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Hacking : ModuleRules
{
	public Hacking(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "VariableStores", "GeneralUtilities", "Slate", "SlateCore", "Niagara", "EnhancedInput", "DamageSystem"});
	}
}
