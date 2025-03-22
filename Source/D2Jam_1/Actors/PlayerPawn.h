// Made during D2Jam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UPassengersCounterComponent;
enum class EGameInactivityReason : uint8;
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

	UFUNCTION(BlueprintGetter)
	float GetRotationSpeed() const { return RotationSpeed; }

	UFUNCTION(BlueprintGetter)
	FVector GetDesiredDirection() const { return DesiredDirection; }

	UFUNCTION(BlueprintGetter)
	FVector GetMouseWorldPosition() const { return MouseWorldPosition; }

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UFloatingPawnMovement> MovementComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UHitPointsComponent> HitPointsComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> Root = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPassengersCounterComponent> PassengersCounterComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetRotationSpeed, Category = "Movement")
	float RotationSpeed = 180.f;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetDesiredDirection, Category="Movement")
	FVector DesiredDirection = FVector::ZeroVector;

	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetMouseWorldPosition, Category="Movement")
	FVector MouseWorldPosition = FVector::ZeroVector;

	UFUNCTION()
	void HandleAnyDamage(AActor* DamagedActor,
	                     float Damage,
	                     const UDamageType* DamageType,
	                     AController* InstigatedBy,
	                     AActor* DamageCauser);

	UFUNCTION()
	void HandleHitPointsReachedZero(UHitPointsComponent* Component);

	UFUNCTION()
	void HandleGameStarted();

	UFUNCTION()
	void HandleGameStopped(EGameInactivityReason InactivityReason);

private:
	UPROPERTY()
	APlayerController* PlayerController = nullptr;

	UPROPERTY()
	APlayerCameraManager* CameraManager = nullptr;

	UFUNCTION()
	void RotateTowardsCursor(const float DeltaTime);
};

