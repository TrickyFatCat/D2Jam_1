// Made during D2Jam

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PassengersCounterComponent.generated.h"


enum class EPlanetColor : uint8;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class D2JAM_1_API UPassengersCounterComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPassengersCounterComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PassengersCounter")
	int32 DefaultPassengersCapacity = 10;
	
	UFUNCTION(BlueprintGetter)
	int32 GetTotalPassengers() const { return TotalPassengers; }

	UFUNCTION(BlueprintGetter)
	int32 GetPassengersCapacity() const { return PassengersCapacity;}
	
	UFUNCTION(BlueprintCallable)
	bool AddPassenger(const EPlanetColor Passenger);

	UFUNCTION(BlueprintCallable, Category="PassengersCounter")
	bool RemovePassengers(const EPlanetColor Passenger);
	
	
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
