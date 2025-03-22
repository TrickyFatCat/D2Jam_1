// Made during D2Jam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UHitPointsComponent;
class UFloatingPawnMovement;

UCLASS()
class D2JAM_1_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UFloatingPawnMovement> MovementComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UHitPointsComponent> HitPointsComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> Root = nullptr;

	UFUNCTION()
	void HandleAnyDamage(AActor* DamagedActor,
	                     float Damage,
	                     const UDamageType* DamageType,
	                     AController* InstigatedBy,
	                     AActor* DamageCauser);
};

