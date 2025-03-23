// Made during D2Jam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlanetsManager.generated.h"

class UPassengersCounterComponent;
enum class EGameResult : uint8;
enum class EPlanetColor : uint8;
enum class EGameInactivityReason : uint8;
class UPlanetColors;
class APlanetBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlanetActivatedDynamicSignature,
                                             APlanetsManager*, Manager,
                                             EPlanetColor, PlanetColor,
                                             int32, ActivePlanetsNum);

UCLASS()
class D2JAM_1_API APlanetsManager : public AActor
{
	GENERATED_BODY()

public:
	APlanetsManager();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnPlanetActivatedDynamicSignature OnPlanetActivated;
	
	UFUNCTION(BlueprintGetter, Category = "PlanetsManager")
	int32 GetCurrentActivePlanetsNum() const { return CurrentActivePlanetsNum; }

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Components")
	TArray<APlanetBase*> Planets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlanetsManager")
	UPlanetColors* PlanetColors = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlanetsManager")
	UCurveFloat* PlanetsActivationCurve = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlanetsManager", meta = (ClampMin = "2", UIMin = "2"))
	int32 InitialActivePlanetsNum = 2;

	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetCurrentActivePlanetsNum, Category = "PlanetsManager")
	int32 CurrentActivePlanetsNum = 2;

private:
	UFUNCTION()
	void RandomizePlanets();

	UFUNCTION()
	void HandleGameStarted();

	UFUNCTION()
	void HandleGameStopped(EGameInactivityReason InactivityReason);

	UFUNCTION()
	void HandleGameFinished(EGameResult GameResult);

	UFUNCTION()
	void HandleTotalPassengersIncreased(UPassengersCounterComponent* Component, int32 TotalPassengers);

	UFUNCTION(BlueprintCallable, Category = "PlanetsManager")
	bool ActivateNextPlanet();

	UFUNCTION()
	void ResetPlanetsState();
};

