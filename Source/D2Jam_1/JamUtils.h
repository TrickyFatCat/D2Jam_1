// Made during D2Jam

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JamUtils.generated.h"

enum class EPlanetColor : uint8;
/**
 * 
 */
UCLASS()
class D2JAM_1_API UJamUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category=JamUtils)
	static bool ProjectMouseToWorld(const APlayerController* PlayerController,
	                                const APlayerCameraManager* CameraManager,
	                                const float Distance,
	                                FVector& MousePosition);

	UFUNCTION(BlueprintPure, Category=JamUtils)
	static int32 CountPassengers(const TArray<EPlanetColor>& Passengers, EPlanetColor Color);
};
