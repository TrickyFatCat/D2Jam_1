// Made during D2Jam


#include "JamUtils.h"

#include "Kismet/KismetMathLibrary.h"


bool UJamUtils::ProjectMouseToWorld(const APlayerController* PlayerController,
                                    const APlayerCameraManager* CameraManager,
                                    const float Distance,
                                    FVector& MousePosition)
{
	if (!IsValid(PlayerController) || !IsValid(CameraManager))
	{
		MousePosition = FVector::ZeroVector;
		return false;
	}

	FVector Location, Direction, Intersection;
	float T = 0.f;

	if (!PlayerController->DeprojectMousePositionToWorld(Location, Direction))
	{
		return false;
	}

	const FVector LineStart = CameraManager->GetCameraLocation();
	const FVector LineEnd = LineStart + Direction * Distance;
	UKismetMathLibrary::LinePlaneIntersection_OriginNormal(LineStart,
	                                                       LineEnd,
	                                                       FVector::ZeroVector,
	                                                       FVector::UpVector,
	                                                       T,
	                                                       Intersection);
	MousePosition = Intersection;
	return true;
}

int32 UJamUtils::CountPassengers(const TArray<EPlanetColor>& Passengers, EPlanetColor Color)
{
	auto Predicate = [Color](const EPlanetColor Passenger)
	{
		return Passenger == Color;
	};

	const int32 Result = Passengers.FilterByPredicate(Predicate).Num();
	return Result;
}
