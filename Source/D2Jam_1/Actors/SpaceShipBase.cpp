// Made during D2Jam


#include "SpaceShipBase.h"


ASpaceShipBase::ASpaceShipBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpaceShipBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentSpeed = FMath::RandRange(MinSpeed, MaxSpeed);
}

void ASpaceShipBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(GetActorForwardVector() * CurrentSpeed * DeltaTime);
}

