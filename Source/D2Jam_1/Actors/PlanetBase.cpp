// Made during D2Jam


#include "PlanetBase.h"

#include "Components/SphereComponent.h"
#include "D2Jam_1/Components/PassengersCounterComponent.h"
#include "D2Jam_1/Components/PassengersGeneratorComponent.h"
#include "GameplayObject/GameplayObjectStateControllerComponent.h"
#include "Kismet/KismetMathLibrary.h"


APlanetBase::APlanetBase()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerComponent = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerComponent"));
	TriggerComponent->SetupAttachment(GetRootComponent());

	PassengersGeneratorComponent = CreateDefaultSubobject<
		UPassengersGeneratorComponent>("PassengersGeneratorComponent");
}

void APlanetBase::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();
	TriggerComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &APlanetBase::HandleTriggerOverlap);
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

	if (!IsValid(MeshComponent))
	{
		return;
	}

	UMaterialInterface* NewMaterial = *PlanetMaterials.Find(PlanetColor);
	MeshComponent->SetMaterial(0, NewMaterial);
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

	if (StateComponent->GetCurrentState() == EGameplayObjectState::Inactive)
	{
		TriggerComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		MeshComponent->SetMaterial(0, InactiveMaterial);
	}
	
	HandlePlanetRandomized();
}

void APlanetBase::HandleStateChanged(UGameplayObjectStateControllerComponent* Component,
                                     EGameplayObjectState NewState,
                                     bool bChangedImmediately)
{
	UMaterialInterface* NewMaterial = nullptr;
	
	switch (NewState)
	{
	case EGameplayObjectState::Active:
		PassengersGeneratorComponent->StartGenerator();
		TriggerComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		NewMaterial = *PlanetMaterials.Find(PlanetColor);
		MeshComponent->SetMaterial(0, NewMaterial);
		break;
	case EGameplayObjectState::Inactive:
		PassengersGeneratorComponent->StopGenerator();
		TriggerComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		MeshComponent->SetMaterial(0, InactiveMaterial);
		break;
	case EGameplayObjectState::Disabled:
		break;
	case EGameplayObjectState::Transition:
		break;
	}
}

void APlanetBase::HandleTriggerOverlap(UPrimitiveComponent* OverlappedComponent,
                                       AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp,
                                       int32 OtherBodyIndex,
                                       bool bFromSweep,
                                       const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor))
	{
		return;
	}

	UPassengersCounterComponent* Component = Cast<UPassengersCounterComponent>(
		OtherActor->GetComponentByClass(UPassengersCounterComponent::StaticClass()));

	if (!IsValid(Component))
	{
		return;
	}

	if (Component->RemovePassengers(PlanetColor))
	{
		HandlePassengersArrived(OtherActor);
	}

	const int32 RemainingCapacity = Component->GetRemainingCapacity();
	const int32 PassengersNum = PassengersGeneratorComponent->GetPassengers().Num();
	const int32 PassengersToBoard = FMath::Min(RemainingCapacity, PassengersNum);

	if (PassengersToBoard <= 0)
	{
		return;
	}

	for (int32 i = 0; i < PassengersToBoard; ++i)
	{
		EPlanetColor Passenger = PassengersGeneratorComponent->BoardPassenger();
		Component->AddPassenger(Passenger);
	}
}
