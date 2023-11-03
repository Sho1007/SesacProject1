// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Weapon/WeaponBase.h"
#include "ThousandEdge.generated.h"

/**
 * 
 */
class AProjectileBase;
UCLASS()
class MYPROJECT_API AThousandEdge : public AWeaponBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void ThrowDagger();
	virtual void Attach(AActor* OwningCharacter) override;
private:
	virtual void Attack() override;
	void PrepareProjectile();
private:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	TSubclassOf<AProjectileBase> ProjectileClass;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	int32 PoolLimit;
	FTimerHandle AttackHandle;
	TArray<AProjectileBase*> ProjectilePool;
};