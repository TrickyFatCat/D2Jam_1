// Made during D2Jam


#include "StellarObject.h"

#include "GameplayObject/GameplayObjectStateControllerComponent.h"
#include "Kismet/GameplayStatics.h"


AStellarObject::AStellarObject()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());

	StateComponent = CreateDefaultSubobject<UGameplayObjectStateControllerComponent>(TEXT("StateComponent"));
}

void AStellarObject::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AStellarObject::HandleBodyOverlap);
	StateComponent->OnGameplayObjectStateChanged.AddUniqueDynamic(this, &AStellarObject::HandleStateChanged);
}

void AStellarObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AStellarObject::ActivateGameplayObject_Implementation(const bool bTransitImmediately)
{
	return Execute_ActivateGameplayObject(StateComponent, bTransitImmediately);
}

bool AStellarObject::DeactivateGameplayObject_Implementation(const bool bTransitImmediately)
{
	return Execute_DeactivateGameplayObject(StateComponent, bTransitImmediately);
}

bool AStellarObject::DisableGameplayObject_Implementation(const bool bTransitImmediately)
{
	return Execute_DisableGameplayObject(StateComponent, bTransitImmediately);
}

bool AStellarObject::EnableGameplayObject_Implementation(const bool bTransitImmediately)
{
	return Execute_EnableGameplayObject(StateComponent, bTransitImmediately);
}

bool AStellarObject::ForceGameplayObjectState_Implementation(const EGameplayObjectState NewState,
                                                             const bool bTransitImmediately)
{
	return Execute_ForceGameplayObjectState(StateComponent, NewState, bTransitImmediately);
}

bool AStellarObject::FinishGameplayObjetStateTransition_Implementation()
{
	return Execute_FinishGameplayObjetStateTransition(StateComponent);
}

bool AStellarObject::ReverseGameplayObjectStateTransition_Implementation()
{
	return Execute_ReverseGameplayObjectStateTransition(StateComponent);
}

void AStellarObject::HandleBodyOverlap(UPrimitiveComponent* OverlappedComponent,
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

	UGameplayStatics::ApplyDamage(OtherActor, ImpactDamage, nullptr, this, nullptr);

	if (bDestroyOnImpact)
	{
		Destroy();
	}
}

void AStellarObject::HandleStateChanged(UGameplayObjectStateControllerComponent* Component,
                                        EGameplayObjectState NewState,
                                        bool bChangedImmediately)
{
}
