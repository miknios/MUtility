// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MUtility : ModuleRules
{
	public MUtility(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", 
				"AIModule",
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"PhysicsCore",
				"DeveloperSettings"
			}
		);

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new[]
			{
				"MessageLog" 
			});
		}
	}
}