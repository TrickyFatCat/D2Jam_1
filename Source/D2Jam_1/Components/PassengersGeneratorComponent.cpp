// Made during D2Jam


#include "PassengersGeneratorComponent.h"

#include "TrickyGameModeBase.h"
#include "TrickyGameModeLibrary.h"
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

void UPassengersGeneratorComponent::ResetPassengers()
{
	PassengerCapacity = DefaultPassengerCapacity;
	Passengers.Empty();
	ArrivedPassengers = 0;
}

void UPassengersGeneratorComponent::StartGenerator()
{
	UWorld* World = GetWorld();

	if (!IsValid(World))
	{
		return;
	}

	FTimerManager& TimerManager = World->GetTimerManager();

	if (TimerManager.IsTimerActive(GenerationTimerHandle))
	{
		return;
	}

	const float Interval = IsValid(GenerationDelayCurve)
		                       ? GenerationDelayCurve->GetFloatValue(ArrivedPassengers)
		                       : DefaultGenerationDelay;
	TimerManager.SetTimer(GenerationTimerHandle, this, &UPassengersGeneratorComponent::HandleGenerationTimer, Interval);
}

void UPassengersGeneratorComponent::StopGenerator()
{
	UWorld* World = GetWorld();

	if (!IsValid(World))
	{
		return;
	}

	FTimerManager& TimerManager = World->GetTimerManager();

	TimerManager.ClearTimer(GenerationTimerHandle);
	TimerManager.ClearTimer(GameOverTimerHandle);
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

EPlanetColor UPassengersGeneratorComponent::BoardPassenger()
{
	const EPlanetColor Passenger = Passengers.Pop();
	ArrivedPassengers++;

	if (Passengers.Num() <= PassengerCapacity)
	{
		StopGameOverTimer();
		StartGenerator();
	}

	OnPassengerBoarded.Broadcast(this, Passenger);
	return Passenger;
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
	OnPassengerGenerated.Broadcast(this, PassengerColor);
	return true;
}

void UPassengersGeneratorComponent::HandleGenerationTimer()
{
	AddRandomPassenger();

	if (Passengers.Num() >= PassengerCapacity)
	{
		StartGameOverTimer();
		return;
	}

	UWorld* World = GetWorld();

	if (!IsValid(World))
	{
		return;
	}

	FTimerManager& TimerManager = World->GetTimerManager();
	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, FName("StartGenerator"));
	TimerManager.SetTimerForNextTick(Delegate);
}

void UPassengersGeneratorComponent::StartGameOverTimer()
{
	UWorld* World = GetWorld();

	if (!IsValid(World))
	{
		return;
	}
	FTimerManager& TimerManager = World->GetTimerManager();

	if (TimerManager.IsTimerActive(GameOverTimerHandle))
	{
		return;
	}

	TimerManager.SetTimer(GameOverTimerHandle,
	                      this,
	                      &UPassengersGeneratorComponent::HandleGameOverTimer,
	                      GameOverDelay);
	OnGameOverTimerStarted.Broadcast(this, GameOverTimerHandle);
}

void UPassengersGeneratorComponent::StopGameOverTimer()
{
	UWorld* World = GetWorld();

	if (!IsValid(World))
	{
		return;
	}

	FTimerManager& TimerManager = World->GetTimerManager();
	TimerManager.ClearTimer(GameOverTimerHandle);
	OnGameOverTimerStopped.Broadcast(this, GameOverTimerHandle);
}

void UPassengersGeneratorComponent::HandleGameOverTimer()
{
	UTrickyGameModeLibrary::FinishGame(this, EGameResult::None);
}
