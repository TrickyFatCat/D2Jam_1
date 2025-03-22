// Made during D2Jam


#include "StellarObject.h"

#include "GameplayObject/GameplayObjectStateControllerComponent.h"
#include "Kismet/GameplayStatics.h"


AStellarObject::AStellarObject()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(MeshComponent);

	StateComponent = CreateDefaultSubobject<UGameplayObjectStateControllerComponent>(TEXT("StateComponent"));
}

void AStellarObject::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AStellarObject::HandleBodyOverlap);
}

void AStellarObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
