// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Weapon/WeaponBase.h"
#include "Bible.generated.h"

/**
 * 
 */

class ABibleProjectile;
UCLASS()
class MYPROJECT_API ABible : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION(CallInEditor)
	void AddProjectile();

	virtual void Tick(float DeltaSeconds) override;
	virtual void Attack() override;

	virtual void Attach(AActor* OwningCharacter) override;

	virtual void LevelUp() override;

	UFUNCTION()
	void UpdateArea(float NewArea);

private:
	void SetAreaAndRotation();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Bible", Meta = (AllowPrivateAccess))
	bool bIsAttacking;
	UPROPERTY(EditDefaultsOnly, Category = "Bible", Meta = (AllowPrivateAccess))
	float BaseSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Bible", Meta = (AllowPrivateAccess))
	float BaseArea;
	UPROPERTY(EditDefaultsOnly, Category = "Bible", Meta = (AllowPrivateAccess))
	TArray<ABibleProjectile*> ProjectileArray;
	UPROPERTY(EditDefaultsOnly, Category = "Bible", Meta = (AllowPrivateAccess))
	TSubclassOf<ABibleProjectile> BibleProjectileClass;
};