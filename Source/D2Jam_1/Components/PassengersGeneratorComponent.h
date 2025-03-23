// Made during D2Jam

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "D2Jam_1/Misc/PlanetColors.h"
#include "PassengersGeneratorComponent.generated.h"

enum class EPlanetColor : uint8;
class UPlanetColors;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNewPassengerAddedDynamicSignature,
                                             UPassengersGeneratorComponent*, Component,
                                             EPlanetColor, PassengerColor);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class D2JAM_1_API UPassengersGeneratorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPassengersGeneratorComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnNewPassengerAddedDynamicSignature OnNewPassengerAdded;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PassengersGenerator")
	int32 DefaultPassengerCapacity = 12;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="PassengersGenerator")
	int32 MaxPossibleColors = 3;

	UFUNCTION()
	bool IncrementPossibleColors();

	UFUNCTION(BlueprintGetter)
	int32 GetPassengerCapacity() const { return PassengerCapacity; }

	UFUNCTION(BlueprintGetter)
	TArray<EPlanetColor> GetPassengers() const { return Passengers; }

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

	UFUNCTION(BlueprintCallable, Category="PassengersGenerator")
	bool IncreaseCapacity(const int32 Amount);

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetPassengerCapacity, Category="PassengersGenerator")
	int32 PassengerCapacity = 12;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="PassengersGenerator")
	int32 CurrentPossibleColors = 2;

	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetPassengers, Category="PassengersGenerator")
	TArray<EPlanetColor> Passengers;

	UPROPERTY(VisibleInstanceOnly, Category="PassengersGenerator")
	UPlanetColors* PlanetColors = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="PassengersGenerator")
	EPlanetColor ExcludedColor = EPlanetColor::Red;

	UPROPERTY()
	FTimerHandle GenerationTimerHandle;

	UFUNCTION(BlueprintCallable)
	bool AddRandomPassenger();
};
