using UnrealBuildTool;

public class ComboGraphHeartProxy : ModuleRules
{
    public ComboGraphHeartProxy(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Heart",
                "HeartCore",
                "HeartCanvas",
                "GameplayTags",
                "ComboGraph"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore"
            }
        );
    }
}