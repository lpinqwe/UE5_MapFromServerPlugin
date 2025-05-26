using UnrealBuildTool;

public class MyChunkLoaderPlugin : ModuleRules
{
    public MyChunkLoaderPlugin(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "Landscape", "HTTP", "Json"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}