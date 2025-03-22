// Made during D2Jam


#include "PlayerPawn.h"

#include "D2Jam_1/Components/HitPointsComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	HitPointsComponent = CreateDefaultSubobject<UHitPointsComponent>(TEXT("HitPointsComponent"));

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);
}

void APlayerPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void APlayerPawn::BeginPlay()
{
	OnTakeAnyDamage.AddDynamic(this, &APlayerPawn::HandleAnyDamage);
	Super::BeginPlay();
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerPawn::HandleAnyDamage(AActor* DamagedActor,
                                  float Damage,
                                  const UDamageType* DamageType,
                                  AController* InstigatedBy,
                                  AActor* DamageCauser)
{
	if (IsValid(HitPointsComponent))
	{
		HitPointsComponent->DecreaseHitPoints(Damage);
	}
}
