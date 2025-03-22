// Made during D2Jam


#include "PlanetsManager.h"

#include "GameStateControllerInterface.h"
#include "PlanetBase.h"
#include "TrickyGameModeBase.h"
#include "TrickyGameModeLibrary.h"
#include "Algo/RandomShuffle.h"
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

	ATrickyGameModeBase* GameMode = UTrickyGameModeLibrary::GetTrickyGameMode(this);

	if (IsValid(GameMode))
	{
		GameMode->OnGameStopped.AddUniqueDynamic(this, &APlanetsManager::HandleGameStopped);
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

inline void APlanetsManager::HandleGameStopped(EGameInactivityReason InactivityReason)
{
	if (InactivityReason != EGameInactivityReason::Transition)
	{
		return;
	}

	RandomizePlanets();
}
