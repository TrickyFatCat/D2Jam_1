// Made during D2Jam


#include "PassengersGeneratorComponent.h"


UPassengersGeneratorComponent::UPassengersGeneratorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UPassengersGeneratorComponent::InitializeComponent()
{
	Super::InitializeComponent();

	PassengerCapacity = DefaultPassengerCapacity;
}

void UPassengersGeneratorComponent::StartGenerator()
{
}

void UPassengersGeneratorComponent::StopGenerator()
{
}

void UPassengersGeneratorComponent::RestartGenerator()
{
	PassengerCapacity = DefaultPassengerCapacity;
	StartGenerator();
}
