// Made during D2Jam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StellarObject.generated.h"

class UGameplayObjectStateControllerComponent;

UCLASS()
class D2JAM_1_API AStellarObject : public AActor
{
	GENERATED_BODY()

public:
	AStellarObject();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> Root = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UGameplayObjectStateControllerComponent> StateComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StellarObject")
	int ImpactDamage = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StellarObject")
	bool bDestroyOnImpact = false;

private:
	UFUNCTION()
	virtual void HandleBodyOverlap(UPrimitiveComponent* OverlappedComponent,
	                               AActor* OtherActor,
	                               UPrimitiveComponent* OtherComp,
	                               int32 OtherBodyIndex,
	                               bool bFromSweep,
	                               const FHitResult& SweepResult);
};
