using UnrealBuildTool;

public class MUtilityEditor : ModuleRules
{
    public MUtilityEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
	            "MUtility",
	            
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
            }
        );
    }
}