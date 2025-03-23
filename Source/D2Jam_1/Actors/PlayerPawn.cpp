// Made during D2Jam


#include "PlayerPawn.h"

#include "TrickyGameModeBase.h"
#include "TrickyGameModeLibrary.h"
#include "D2Jam_1/JamUtils.h"
#include "D2Jam_1/Components/HitPointsComponent.h"
#include "D2Jam_1/Components/PassengersCounterComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"


class ATrickyGameModeBase;

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	HitPointsComponent = CreateDefaultSubobject<UHitPointsComponent>(TEXT("HitPointsComponent"));
	PassengersCounterComponent = CreateDefaultSubobject<
		UPassengersCounterComponent>(TEXT("PassengersCounterComponent"));

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);
}

void APlayerPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &APlayerPawn::HandleAnyDamage);
	PlayerController = Cast<APlayerController>(GetController());
	CameraManager = PlayerController->PlayerCameraManager;

	if (IsValid(HitPointsComponent))
	{
		HitPointsComponent->OnHitPointsReachedZero.AddUniqueDynamic(this, &APlayerPawn::HandleHitPointsReachedZero);
	}

	ATrickyGameModeBase* GameMode = UTrickyGameModeLibrary::GetTrickyGameMode(this);

	if (IsValid(GameMode))
	{
		GameMode->OnGameStarted.AddUniqueDynamic(this, &APlayerPawn::HandleGameStarted);
		GameMode->OnGameStopped.AddUniqueDynamic(this, &APlayerPawn::HandleGameStopped);
		GameMode->OnGameFinished.AddUniqueDynamic(this, &APlayerPawn::HandleGameFinished);
	}

	if (IsValid(MovementComponent))
	{
		MovementComponent->SetComponentTickEnabled(false);
	}

	if (IsValid(PassengersCounterComponent))
	{
		PassengersCounterComponent->OnTotalPassengersIncreased.AddUniqueDynamic(this,
			&APlayerPawn::HandleTotalPassengersIncreased);
		HandleTotalPassengersIncreased(PassengersCounterComponent, 0);
	}
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(MovementComponent) && MovementComponent->IsComponentTickEnabled())
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

void APlayerPawn::HandleHitPointsReachedZero(UHitPointsComponent* Component)
{
	MovementComponent->SetComponentTickEnabled(false);
	UTrickyGameModeLibrary::FinishGame(this, EGameResult::None);
}

void APlayerPawn::HandleGameStarted()
{
	MovementComponent->SetComponentTickEnabled(true);
}

void APlayerPawn::HandleGameStopped(EGameInactivityReason InactivityReason)
{
	if (InactivityReason != EGameInactivityReason::Transition)
	{
		return;
	}

	MovementComponent->Velocity = FVector::ZeroVector;
	HitPointsComponent->ResetHitPointsToMax();
	PassengersCounterComponent->ResetPassengers();
	SetActorTransform(FTransform::Identity);
	HandleTotalPassengersIncreased(PassengersCounterComponent, 0);
}

void APlayerPawn::HandleGameFinished(EGameResult GameResult)
{
	MovementComponent->SetComponentTickEnabled(false);
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

void APlayerPawn::HandleTotalPassengersIncreased(UPassengersCounterComponent* Component, int32 TotalPassengers)
{
	if (!IsValid(SpeedProgressionCurve) || !IsValid(MovementComponent))
	{
		return;
	}

	const float NewSpeed = SpeedProgressionCurve->GetFloatValue(TotalPassengers);
	MovementComponent->MaxSpeed = NewSpeed;
}
