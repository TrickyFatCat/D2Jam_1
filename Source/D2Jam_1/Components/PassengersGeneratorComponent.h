// Made during D2Jam

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "D2Jam_1/Misc/PlanetColors.h"
#include "PassengersGeneratorComponent.generated.h"

enum class EPlanetColor : uint8;
class UPlanetColors;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPassengerGeneratedDynamicSignature,
                                             UPassengersGeneratorComponent*, Component,
                                             EPlanetColor, PassengerColor);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPassengerBoardedDynamicSignature,
                                             UPassengersGeneratorComponent*, Component,
                                             EPlanetColor, PassengerColor);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameOverTimerStartedDynamicSignature,
                                             UPassengersGeneratorComponent*, Component,
                                             FTimerHandle, Timer);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameOverTimerStoppedDynamicSignature,
                                             UPassengersGeneratorComponent*, Component,
                                             FTimerHandle, Timer);

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
	FOnPassengerGeneratedDynamicSignature OnPassengerGenerated;

	UPROPERTY(BlueprintAssignable)
	FOnPassengerBoardedDynamicSignature OnPassengerBoarded;

	UPROPERTY(BlueprintAssignable)
	FOnGameOverTimerStartedDynamicSignature OnGameOverTimerStarted;

	UPROPERTY(BlueprintAssignable)
	FOnGameOverTimerStoppedDynamicSignature OnGameOverTimerStopped;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PassengersGenerator")
	int32 DefaultPassengerCapacity = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PassengersGenerator")
	int32 MaxPossibleColors = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PassengersGenerator")
	UCurveFloat* GenerationDelayCurve = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PassengersGenerator")
	float DefaultGenerationDelay = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PassengersGenerator")
	float GameOverDelay = 10.f;

	UFUNCTION()
	bool IncrementPossibleColors();

	UFUNCTION(BlueprintGetter)
	int32 GetPassengerCapacity() const { return PassengerCapacity; }

	UFUNCTION(BlueprintGetter)
	TArray<EPlanetColor> GetPassengers() const { return Passengers; }

	UFUNCTION()
	void ResetPassengers();

	UFUNCTION()
	void SetPlanetColors(UPlanetColors* Value) { PlanetColors = Value; }

	UFUNCTION()
	void SetExcludedColor(const EPlanetColor Value) { ExcludedColor = Value; }

	UFUNCTION()
	void StartGenerator();

	UFUNCTION()
	void StopGenerator();

	UFUNCTION(BlueprintCallable, Category="PassengersGenerator")
	bool IncreaseCapacity(const int32 Amount);

	UFUNCTION(BlueprintCallable, Category="PassengersGenerator")
	EPlanetColor BoardPassenger();

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetPassengerCapacity, Category="PassengersGenerator")
	int32 PassengerCapacity = 12;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="PassengersGenerator")
	int32 CurrentPossibleColors = 1;

	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetPassengers, Category="PassengersGenerator")
	TArray<EPlanetColor> Passengers;

	UPROPERTY(VisibleInstanceOnly, Category="PassengersGenerator")
	UPlanetColors* PlanetColors = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="PassengersGenerator")
	EPlanetColor ExcludedColor = EPlanetColor::Red;

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle GenerationTimerHandle;

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle GameOverTimerHandle;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category="PassengersGenerator")
	int32 ArrivedPassengers = 0;

	UFUNCTION(BlueprintCallable)
	bool AddRandomPassenger();

	UFUNCTION()
	void HandleGenerationTimer();

	UFUNCTION()
	void StartGameOverTimer();

	UFUNCTION()
	void StopGameOverTimer();

	UFUNCTION()
	void HandleGameOverTimer();
};
