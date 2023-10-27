// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ObjectPooling/ProjectileBase.h"
#include "BibleProjectile.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ABibleProjectile : public AProjectileBase
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void Activate() override;

	void SetDuration(float NewDuration);
protected:
	virtual void Attack(AActor* TargetActor) override;

	

private:
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	float MultiAttackAvoidTime;
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	float ActiveTime;
	UPROPERTY(Meta = (AllowPrivateAccess))
	TMap<FString, float> CollisionMap;
};