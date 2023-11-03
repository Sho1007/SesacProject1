// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ObjectPooling/PoolingActor.h"
#include "ProfilingDebugging/ExternalProfiler.h"
#include "BossBoxBase.generated.h"

/**
 * 
 */
class UStaticMeshComponent;
class UBoxComponent;
class ACharacter;
UCLASS()
class MYPROJECT_API ABossBoxBase : public APoolingActor
{
	GENERATED_BODY()

public:
	ABossBoxBase();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OpenBox(ACharacter* TargetCharacter);

	virtual void Activate() override;
	virtual void Deactivate() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Collider;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BoxMesh;

	UPROPERTY(EditDefaultsOnly)
	float ChanceTo5;
	UPROPERTY(EditDefaultsOnly)
	float ChanceTo3;
};