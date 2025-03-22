// Made during D2Jam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlanetsManager.generated.h"

enum class EGameInactivityReason : uint8;
class UPlanetColors;
class APlanetBase;

UCLASS()
class D2JAM_1_API APlanetsManager : public AActor
{
	GENERATED_BODY()

public:
	APlanetsManager();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Components")
	TArray<APlanetBase*> Planets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlanetsManager")
	UPlanetColors* PlanetColors = nullptr;

private:
	UFUNCTION()
	void RandomizePlanets();

	UFUNCTION()
	void HandleGameStopped(EGameInactivityReason InactivityReason);
};


