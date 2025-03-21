// Made during D2Jam

using UnrealBuildTool;
using System.Collections.Generic;

public class D2Jam_1EditorTarget : TargetRules
{
	public D2Jam_1EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "D2Jam_1" } );
	}
}
