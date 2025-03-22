// Made during D2Jam


#include "HitPointsComponent.h"

#include "TrickyPropertiesLibrary.h"
#include "TrickyPropertyInt.h"


UHitPointsComponent::UHitPointsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UHitPointsComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	SetComponentTickEnabled(false);
	HitPoints = DefaultHitPoints;
}

bool UHitPointsComponent::DecreaseHitPoints(const int32 Amount)
{
	if (Amount <= 0 || HasReachedZero())
	{
		return false;
	}

	if (!UTrickyPropertiesLibrary::DecreaseValueInt(HitPoints, Amount))
	{
		return false;
	}

	UTrickyPropertiesLibrary::ClampToMinInt(HitPoints);
	OnHitPointsDecreased.Broadcast(this, HitPoints.Value);

	if (UTrickyPropertiesLibrary::ReachedMinValueInt(HitPoints))
	{
		OnHitPointsReachedZero.Broadcast(this);
	}

	return true;
}

bool UHitPointsComponent::ResetHitPointsToMax()
{
	if (!HasReachedZero())
	{
		return false;
	}

	UTrickyPropertiesLibrary::ResetToMaxValueInt(HitPoints);
	return true;
}

bool UHitPointsComponent::HasReachedZero()
{
	return UTrickyPropertiesLibrary::ReachedMinValueInt(HitPoints);
}
