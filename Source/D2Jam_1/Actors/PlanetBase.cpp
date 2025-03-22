// Made during D2Jam


#include "PlanetBase.h"

#include "TrickyGameModeLibrary.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"


APlanetBase::APlanetBase()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerComponent = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerComponent"));
	TriggerComponent->SetupAttachment(MeshComponent);
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
}

void APlanetBase::SetPlanetColor(const EPlanetColor NewPlanetColor, const FLinearColor NewColor)
{
	PlanetColor = NewPlanetColor;
	Color = NewColor;
}

void APlanetBase::RandomizePlanet()
{
	if (RandomizationRadius > 0.f)
	{
		FVector Direction = UKismetMathLibrary::RandomUnitVector();
		Direction.Z = 0.f;
		Direction.Normalize();
		const FVector NewLocation = InitialLocation + Direction * UKismetMathLibrary::RandomFloatInRange(0.f, RandomizationRadius);
		SetActorLocation(NewLocation);
	}
	
	HandlePlanetRandomized();
}

