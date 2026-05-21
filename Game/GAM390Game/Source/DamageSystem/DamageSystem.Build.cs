// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DamageSystem : ModuleRules
{
	public DamageSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "PhysicsCore"});
	}
}
