// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Weapon/WeaponBase.h"
#include "Bible.generated.h"

/**
 * 
 */

class AProjectileBase;
UCLASS()
class MYPROJECT_API ABible : public AWeaponBase
{
	GENERATED_BODY()


public:
	UFUNCTION(CallInEditor)
	void AddProjectile();

	virtual void Tick(float DeltaSeconds) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	float RotateSpeed;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	float ProjectileDistance;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	TArray<AProjectileBase*> ProjectileArray;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	TSubclassOf<AProjectileBase> BibleProjectileClass;
};