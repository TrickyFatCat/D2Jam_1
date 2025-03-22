// Made during D2Jam

#pragma once

#include "CoreMinimal.h"
#include "TrickyPropertyInt.h"
#include "Components/ActorComponent.h"
#include "D2Jam_1/Misc/PlanetColors.h"
#include "PassengersGeneratorComponent.generated.h"


enum class EPlanetColor : uint8;
class UPlanetColors;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class D2JAM_1_API UPassengersGeneratorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPassengersGeneratorComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PassengersGenerator")
	FTrickyPropertyInt DefaultPassengerCapacity{0, 0, 12};

	UFUNCTION()
	void SetPlanetColors(UPlanetColors* Value) { PlanetColors = Value; }

	UFUNCTION()
	void SetExcludedColor(const EPlanetColor Value) { ExcludedColor = Value; }

	UFUNCTION()
	void StartGenerator();

	UFUNCTION()
	void StopGenerator();

	UFUNCTION()
	void RestartGenerator();
	
protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="PassengersGenerator")
	FTrickyPropertyInt PassengerCapacity;

	UPROPERTY(VisibleInstanceOnly, Category="PassengersGenerator")
	UPlanetColors* PlanetColors = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="PassengersGenerator")
	EPlanetColor ExcludedColor = EPlanetColor::Red;
};
