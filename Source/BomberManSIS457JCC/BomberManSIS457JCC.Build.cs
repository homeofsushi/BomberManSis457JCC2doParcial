// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BomberManSIS457JCC : ModuleRules
{
	public BomberManSIS457JCC(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
