// Made during D2Jam


#include "PlayerPawn.h"

#include "D2Jam_1/JamUtils.h"
#include "D2Jam_1/Components/HitPointsComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"


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
	PlayerController = Cast<APlayerController>(GetController());
	CameraManager = PlayerController->PlayerCameraManager;

	Super::BeginPlay();
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(MovementComponent))
	{
		RotateTowardsCursor(DeltaTime);
		MovementComponent->AddInputVector(GetActorForwardVector());
	}
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

void APlayerPawn::RotateTowardsCursor(const float DeltaTime)
{
	UJamUtils::ProjectMouseToWorld(PlayerController, CameraManager, 100000.f, MouseWorldPosition);
	MouseWorldPosition.Z = 0.f;
	FVector ActorPosition = GetActorLocation();
	ActorPosition.Z = 0.f;
	DesiredDirection = UKismetMathLibrary::GetDirectionUnitVector(ActorPosition, MouseWorldPosition);
	FRotator NewRotation = UKismetMathLibrary::RInterpTo_Constant(GetActorRotation(),
	                                                              DesiredDirection.Rotation(),
	                                                              DeltaTime,
	                                                              RotationSpeed);
	SetActorRotation(NewRotation);
}
