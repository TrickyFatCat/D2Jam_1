// Made during D2Jam

#pragma once

#include "CoreMinimal.h"
#include "TrickyPropertyInt.h"
#include "Components/ActorComponent.h"
#include "HitPointsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHitPointsDecreasedDynamicSignature,
                                             UHitPointsComponent*, Component,
                                             int32, CurrentHitPoints);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHitPointsReachedZeroDynamicSignature,
                                            UHitPointsComponent*, Component);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHitPointsResetToMaxDynamicSignature,
                                             UHitPointsComponent*, Component,
                                             int32, CurrentHitPoints);

UCLASS(ClassGroup=(GameJam), meta=(BlueprintSpawnableComponent))
class D2JAM_1_API UHitPointsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHitPointsComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnHitPointsDecreasedDynamicSignature OnHitPointsDecreased;

	UPROPERTY(BlueprintAssignable)
	FOnHitPointsReachedZeroDynamicSignature OnHitPointsReachedZero;

	UPROPERTY(BlueprintAssignable)
	FOnHitPointsResetToMaxDynamicSignature OnHitPointsResetToMax;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HitPoints")
	FTrickyPropertyInt DefaultHitPoints{0, 3, 3};

	UFUNCTION(BlueprintPure)
	int32 GetCurrentHitPoints() const { return HitPoints.Value; }

	UFUNCTION(BlueprintCallable)
	bool DecreaseHitPoints(const int32 Amount);

	UFUNCTION(BlueprintCallable)
	bool ResetHitPointsToMax();

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "HitPoints")
	FTrickyPropertyInt HitPoints;

	bool HasReachedZero();
};
