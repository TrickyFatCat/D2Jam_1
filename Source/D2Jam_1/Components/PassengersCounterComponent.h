// Made during D2Jam

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PassengersCounterComponent.generated.h"


enum class EPlanetColor : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPassengerAddedDynamicSignature,
                                             UPassengersCounterComponent*, Component,
                                             EPlanetColor, Passenger);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPassengerRemovedDynamicSignature,
                                             UPassengersCounterComponent*, Component,
                                             EPlanetColor, Passenger,
                                             int32, Num);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class D2JAM_1_API UPassengersCounterComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPassengersCounterComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnPassengerAddedDynamicSignature OnPassengerAdded;

	UPROPERTY(BlueprintAssignable)
	FOnPassengerRemovedDynamicSignature OnPassengerRemoved;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PassengersCounter")
	int32 DefaultPassengersCapacity = 10;

	UFUNCTION(BlueprintGetter)
	int32 GetTotalPassengers() const { return TotalPassengers; }

	UFUNCTION(BlueprintGetter)
	int32 GetPassengersCapacity() const { return PassengersCapacity; }

	UFUNCTION(BlueprintCallable)
	bool AddPassenger(const EPlanetColor Passenger);

	UFUNCTION(BlueprintCallable)
	int32 AddPassengers(const EPlanetColor Passenger, const int32 Amount);

	UFUNCTION(BlueprintCallable, Category="PassengersCounter")
	bool RemovePassengers(const EPlanetColor Passenger);

	UFUNCTION(BlueprintCallable, Category="PassengersCounter")
	int32 GetRemainingCapacity() const;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetTotalPassengers, Transient, Category="PassengersCounter")
	int32 TotalPassengers = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetPassengersCapacity, Category="PassengersCounter")
	int32 PassengersCapacity = 10;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="PassengersCounter")
	TArray<EPlanetColor> Passengers;

	UFUNCTION(BlueprintCallable)
	bool IncreasePassengerCapacity(const int32 Amount);

	UFUNCTION(BlueprintCallable)
	void ResetCounter();
};
