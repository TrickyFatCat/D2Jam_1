// Made during D2Jam

#pragma once

#include "CoreMinimal.h"
#include "TrickyPropertyInt.h"
#include "Components/ActorComponent.h"
#include "PassengersCounterComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class D2JAM_1_API UPassengersCounterComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPassengersCounterComponent();

protected:
	virtual void InitializeComponent() override;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category="PassengersCounter")
	int32 TotalPassengers = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PassengersCounter")
	FTrickyPropertyInt DefaultPassengerCapacity{0, 0, 10};

	UFUNCTION(BlueprintGetter)
	FTrickyPropertyInt GetPassengerCapacity() const { return PassengerCapacity; }

	UFUNCTION(BlueprintCallable)
	bool IncreasePassengerCapacity(const int32 Amount);

	UFUNCTION(BlueprintCallable)
	bool IncreasePassengerMaxCapacity(const int32 Amount);

	UFUNCTION(BlueprintCallable)
	void ResetCounter();


private:
	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetPassengerCapacity, Category="PassengersCounter")
	FTrickyPropertyInt PassengerCapacity;
};
