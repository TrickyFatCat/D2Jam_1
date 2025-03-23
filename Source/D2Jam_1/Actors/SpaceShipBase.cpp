// Made during D2Jam


#include "SpaceShipBase.h"

#include "GameFramework/FloatingPawnMovement.h"


ASpaceShipBase::ASpaceShipBase()
{
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
}

void ASpaceShipBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpaceShipBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

