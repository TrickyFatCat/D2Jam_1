// Made during D2Jam


#include "PassengersCounterComponent.h"

#include "TrickyPropertiesLibrary.h"


UPassengersCounterComponent::UPassengersCounterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UPassengersCounterComponent::InitializeComponent()
{
	Super::InitializeComponent();
	ResetCounter();
}

bool UPassengersCounterComponent::AddPassenger(const EPlanetColor Passenger)
{
	if (Passengers.Num() >= PassengersCapacity)
	{
		return false;
	}

	Passengers.Add(Passenger);
	return true;
}

bool UPassengersCounterComponent::RemovePassengers(const EPlanetColor Passenger)
{
	if (Passengers.IsEmpty() || !Passengers.Contains(Passenger))
	{
		return false;
	}

	const int32 RemovePassengersNum = Passengers.Remove(Passenger);
	TotalPassengers += RemovePassengersNum;
	return true;
}

bool UPassengersCounterComponent::IncreasePassengerCapacity(const int32 Amount)
{
	if (Amount <= 0)
	{
		return false;
	}

	PassengersCapacity += Amount;
	return true;
}

void UPassengersCounterComponent::ResetCounter()
{
	PassengersCapacity = DefaultPassengersCapacity;
	TotalPassengers = 0;
}
