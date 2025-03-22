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
}

bool UPassengersCounterComponent::IncreasePassengerCapacity(const int32 Amount)
{
	if (!UTrickyPropertiesLibrary::IncreaseValueInt(PassengerCapacity, Amount))
	{
		return false;
	}

	UTrickyPropertiesLibrary::ClampToMaxInt(PassengerCapacity);
	return true;
}

bool UPassengersCounterComponent::IncreasePassengerMaxCapacity(const int32 Amount)
{
	return UTrickyPropertiesLibrary::IncreaseMaxValueInt(PassengerCapacity, Amount);
}


void UPassengersCounterComponent::ResetCounter()
{
	PassengerCapacity = DefaultPassengerCapacity;
	TotalPassengers = 0;
}
