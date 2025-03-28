﻿// Made during D2Jam


#include "PlanetsManager.h"

#include "GameStateControllerInterface.h"
#include "PlanetBase.h"
#include "TrickyGameModeBase.h"
#include "TrickyGameModeLibrary.h"
#include "Algo/RandomShuffle.h"
#include "D2Jam_1/Components/PassengersCounterComponent.h"
#include "D2Jam_1/Components/PassengersGeneratorComponent.h"
#include "D2Jam_1/Misc/PlanetColors.h"
#include "Kismet/GameplayStatics.h"


APlanetsManager::APlanetsManager()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void APlanetsManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this, APlanetBase::StaticClass(), Actors);

	for (AActor* Actor : Actors)
	{
		Planets.Add(Cast<APlanetBase>(Actor));
		Actor->DispatchBeginPlay();
	}

	RandomizePlanets();

	for (APlanetBase* Planet : Planets)
	{
		if (!IsValid(Planet))
		{
			continue;
		}

		Planet->SetPlanetColors(PlanetColors);
	}

	ResetPlanetsState();

	ATrickyGameModeBase* GameMode = UTrickyGameModeLibrary::GetTrickyGameMode(this);

	if (IsValid(GameMode))
	{
		GameMode->OnGameStarted.AddUniqueDynamic(this, &APlanetsManager::HandleGameStarted);
		GameMode->OnGameStopped.AddUniqueDynamic(this, &APlanetsManager::HandleGameStopped);
		GameMode->OnGameFinished.AddUniqueDynamic(this, &APlanetsManager::HandleGameFinished);
	}

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if (IsValid(PlayerPawn))
	{
		UPassengersCounterComponent* CounterComponent = PlayerPawn->GetComponentByClass<UPassengersCounterComponent>();
		
		if (IsValid(CounterComponent))
		{
			CounterComponent->OnTotalPassengersIncreased.AddUniqueDynamic(this, &APlanetsManager::HandleTotalPassengersIncreased);
		}
	}
}

void APlanetsManager::RandomizePlanets()
{
	if (Planets.IsEmpty())
	{
		return;
	}

	if (IsValid(PlanetColors))
	{
		TMap<EPlanetColor, FLinearColor> Colors = PlanetColors->Colors;
		TArray<EPlanetColor> ColorsKeys;
		Colors.GetKeys(ColorsKeys);

		Algo::RandomShuffle(Planets);

		for (int32 i = 0; i < Planets.Num(); ++i)
		{
			APlanetBase* Planet = Planets[i];

			if (!IsValid(Planet))
			{
				continue;
			}

			const int32 ColorIndex = i % ColorsKeys.Num();
			Planet->SetPlanetColor(ColorsKeys[ColorIndex], Colors[ColorsKeys[ColorIndex]]);
		}
	}

	for (APlanetBase* Planet : Planets)
	{
		Planet->RandomizePlanet();
	}
}

void APlanetsManager::HandleGameStarted()
{
	if (Planets.IsEmpty() || Planets.Num() < InitialActivePlanetsNum)
	{
		return;
	}

	for (int32 i = 0; i < InitialActivePlanetsNum; ++i)
	{
		APlanetBase* Planet = Planets[i];

		if (!IsValid(Planet))
		{
			continue;
		}
		
		IGameplayObjectInterface::Execute_ActivateGameplayObject(Planet, true);
	}
}

inline void APlanetsManager::HandleGameStopped(EGameInactivityReason InactivityReason)
{
	if (InactivityReason != EGameInactivityReason::Transition)
	{
		return;
	}

	RandomizePlanets();
	ResetPlanetsState();
}

void APlanetsManager::HandleGameFinished(EGameResult GameResult)
{
	for (APlanetBase* Planet : Planets)
	{
		if (!IsValid(Planet))
		{
			continue;
		}

		IGameplayObjectInterface::Execute_DeactivateGameplayObject(Planet, true);
	}
}

void APlanetsManager::HandleTotalPassengersIncreased(UPassengersCounterComponent* Component, int32 TotalPassengers)
{
	if (CurrentActivePlanetsNum >= Planets.Num())
	{
		return;
	}
	
	bool bShouldActivatePlanet = false;

	if (!IsValid(PlanetsActivationCurve))
	{
		bShouldActivatePlanet = true;
	}
	else
	{
		const int32 ActivationProgress = PlanetsActivationCurve->GetFloatValue(TotalPassengers);
		bShouldActivatePlanet = ActivationProgress > CurrentActivePlanetsNum;
	}

	if (!bShouldActivatePlanet)
	{
		return;
	}

	ActivateNextPlanet();
}

bool APlanetsManager::ActivateNextPlanet()
{
	if (CurrentActivePlanetsNum >= Planets.Num())
	{
		return false;
	}

	APlanetBase* NextPlanet = Planets[CurrentActivePlanetsNum];

	if (!IsValid(NextPlanet) || !IGameplayObjectInterface::Execute_ActivateGameplayObject(NextPlanet, true))
	{
		return false;
	}

	CurrentActivePlanetsNum++;
	OnPlanetActivated.Broadcast(this, NextPlanet->GetPlanetColor(), CurrentActivePlanetsNum);

	for (const APlanetBase* Planet : Planets)
	{
		if (!IsValid(Planet))
		{
			continue;
		}

		Planet->GetPassengersGeneratorComponent()->IncrementPossibleColors();
	}

	return true;
}

void APlanetsManager::ResetPlanetsState()
{
	CurrentActivePlanetsNum = InitialActivePlanetsNum;

	for (APlanetBase* Planet : Planets)
	{
		if (!IsValid(Planet))
		{
			continue;
		}

		IGameplayObjectInterface::Execute_DeactivateGameplayObject(Planet, true);
		Planet->GetPassengersGeneratorComponent()->ResetPassengers();
	}
}
