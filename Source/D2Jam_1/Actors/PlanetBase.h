// Made during D2Jam

#pragma once

#include "CoreMinimal.h"
#include "StellarObject.h"
#include "D2Jam_1/Misc/PlanetColors.h"
#include "PlanetBase.generated.h"

class UPassengersGeneratorComponent;
class USphereComponent;
class UGameplayObjectStateControllerComponent;

UCLASS()
class D2JAM_1_API APlanetBase : public AStellarObject
{
	GENERATED_BODY()

public:
	APlanetBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetPlanetColors(UPlanetColors* NewPlanetColors);

	UFUNCTION(BlueprintCallable, Category = "Planet")
	void SetPlanetColor(EPlanetColor NewPlanetColor, FLinearColor NewColor);

	UFUNCTION(BlueprintGetter)
	EPlanetColor GetPlanetColor() const { return PlanetColor; }

	UFUNCTION(BlueprintGetter)
	UPassengersGeneratorComponent* GetPassengersGeneratorComponent() const { return PassengersGeneratorComponent; }

	UFUNCTION(BlueprintCallable, Category = "Planet")
	void RandomizePlanet();

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> TriggerComponent = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetPassengersGeneratorComponent, Category = "Components")
	TObjectPtr<UPassengersGeneratorComponent> PassengersGeneratorComponent = nullptr;

	UPROPERTY(VisibleInstanceOnly, Category="Planet")
	UPlanetColors* PlanetColors = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetPlanetColor, Category = "Planet")
	EPlanetColor PlanetColor = EPlanetColor::Red;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Planet")
	FLinearColor Color = FColor::Magenta;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Planet")
	FVector InitialLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Planet")
	float RandomizationRadius = 200.0f;

	UFUNCTION(BlueprintImplementableEvent, Category = "Planet")
	void HandlePlanetRandomized();

	virtual void HandleStateChanged(UGameplayObjectStateControllerComponent* Component,
	                                EGameplayObjectState NewState,
	                                bool bChangedImmediately) override;
};
