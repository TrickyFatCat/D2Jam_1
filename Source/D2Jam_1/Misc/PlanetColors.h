// Made during D2Jam

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlanetColors.generated.h"

UENUM(BlueprintType)
enum class EPlanetColor : uint8
{
	Red,
	Yellow,
	Green,
	Indigo,
	Purple
};

/**
 * 
 */
UCLASS()
class D2JAM_1_API UPlanetColors : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Colors")
	TMap<EPlanetColor, FLinearColor> Colors{
		{EPlanetColor::Red, FLinearColor::Red},
		{EPlanetColor::Yellow, FColor::Yellow},
		{EPlanetColor::Green, FColor::Green},
		{EPlanetColor::Indigo, FColor::Blue},
		{EPlanetColor::Purple, FColor::Purple}
	};
};
