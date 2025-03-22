// Made during D2Jam


#include "PlanetBase.h"

#include "Components/SphereComponent.h"
#include "D2Jam_1/Components/PassengersGeneratorComponent.h"
#include "Kismet/KismetMathLibrary.h"


APlanetBase::APlanetBase()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerComponent = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerComponent"));
	TriggerComponent->SetupAttachment(MeshComponent);

	PassengersGeneratorComponent = CreateDefaultSubobject<
		UPassengersGeneratorComponent>("PassengersGeneratorComponent");
}

void APlanetBase::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();
}

void APlanetBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlanetBase::SetPlanetColors(UPlanetColors* NewPlanetColors)
{
	PlanetColors = NewPlanetColors;

	if (IsValid(PassengersGeneratorComponent))
	{
		PassengersGeneratorComponent->SetPlanetColors(PlanetColors);
	}
}

void APlanetBase::SetPlanetColor(const EPlanetColor NewPlanetColor, const FLinearColor NewColor)
{
	PlanetColor = NewPlanetColor;
	Color = NewColor;

	if (IsValid(PassengersGeneratorComponent))
	{
		PassengersGeneratorComponent->SetExcludedColor(PlanetColor);
	}
}

void APlanetBase::RandomizePlanet()
{
	if (RandomizationRadius > 0.f)
	{
		FVector Direction = UKismetMathLibrary::RandomUnitVector();
		Direction.Z = 0.f;
		Direction.Normalize();
		const FVector NewLocation = InitialLocation + Direction * UKismetMathLibrary::RandomFloatInRange(
			0.f, RandomizationRadius);
		SetActorLocation(NewLocation);
	}

	HandlePlanetRandomized();
}

void APlanetBase::HandleStateChanged(UGameplayObjectStateControllerComponent* Component,
                                     EGameplayObjectState NewState,
                                     bool bChangedImmediately)
{
	switch (NewState) {
	case EGameplayObjectState::Active:
		PassengersGeneratorComponent->StartGenerator();
		break;
	case EGameplayObjectState::Inactive:
		PassengersGeneratorComponent->StopGenerator();
		break;
	case EGameplayObjectState::Disabled:
		break;
	case EGameplayObjectState::Transition:
		break;
	}
}
