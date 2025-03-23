﻿// Made during D2Jam


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

int32 UPassengersCounterComponent::AddPassengers(const EPlanetColor Passenger, const int32 Amount)
{
	if (Passengers.Num() >= PassengersCapacity)
	{
		return 0;
	}

	const int32 AddPassengersNum = FMath::Min(Amount, PassengersCapacity - Passengers.Num());

	for (int32 i = 0; i < AddPassengersNum; i++)
	{
		Passengers.Add(Passenger);
	}
	
	return AddPassengersNum;
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
