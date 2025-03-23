// Made during D2Jam


#include "PassengersGeneratorComponent.h"

#include "D2Jam_1/Actors/PlanetsManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


UPassengersGeneratorComponent::UPassengersGeneratorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UPassengersGeneratorComponent::InitializeComponent()
{
	Super::InitializeComponent();

	PassengerCapacity = DefaultPassengerCapacity;

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this, APlanetsManager::StaticClass(), Actors);
}

bool UPassengersGeneratorComponent::IncrementPossibleColors()
{
	if (CurrentPossibleColors >= MaxPossibleColors)
	{
		return false;
	}

	CurrentPossibleColors++;
	return true;
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

bool UPassengersGeneratorComponent::IncreaseCapacity(const int32 Amount)
{
	if (Amount <= 0)
	{
		return false;
	}

	PassengerCapacity += Amount;
	return true;
}

bool UPassengersGeneratorComponent::AddRandomPassenger()
{
	if (Passengers.Num() >= PassengerCapacity)
	{
		return false;
	}

	TArray<EPlanetColor> PassengerColors;
	PlanetColors->Colors.GetKeys(PassengerColors);
	PassengerColors.Remove(ExcludedColor);
	
	int32 ColorIndex = 0;
	int32 Counter = 0;
	
	do
	{
		ColorIndex = UKismetMathLibrary::RandomIntegerInRange(0, CurrentPossibleColors - 1);
		Counter++;
	}
	while (!PassengerColors.IsValidIndex(ColorIndex) || Counter < 100);

	if (!PassengerColors.IsValidIndex(ColorIndex))
	{
		ColorIndex = 0;
	}
	
	const EPlanetColor PassengerColor = PassengerColors[ColorIndex];
	Passengers.Add(PassengerColor);
	OnNewPassengerAdded.Broadcast(this, PassengerColor);
	return true;
}
