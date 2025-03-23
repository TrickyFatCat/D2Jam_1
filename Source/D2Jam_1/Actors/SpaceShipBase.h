// Made during D2Jam

#pragma once

#include "CoreMinimal.h"
#include "StellarObject.h"
#include "SpaceShipBase.generated.h"

class UFloatingPawnMovement;

UCLASS()
class D2JAM_1_API ASpaceShipBase : public AStellarObject
{
	GENERATED_BODY()

public:
	ASpaceShipBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UFloatingPawnMovement> MovementComponent = nullptr;
};
