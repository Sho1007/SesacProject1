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
	void AddProjectile(int AddCount = 1);

	virtual void Tick(float DeltaSeconds) override;
	virtual void Attack() override;

	virtual void Attach(AActor* OwningCharacter) override;

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bible", Meta = (AllowPrivateAccess))
	float Duration;
	UPROPERTY(EditDefaultsOnly, Category = "Bible", Meta = (AllowPrivateAccess))
	float RotateSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Bible", Meta = (AllowPrivateAccess))
	float ProjectileDistance;
	UPROPERTY(EditDefaultsOnly, Category = "Bible", Meta = (AllowPrivateAccess))
	TArray<ABibleProjectile*> ProjectileArray;
	UPROPERTY(EditDefaultsOnly, Category = "Bible", Meta = (AllowPrivateAccess))
	TSubclassOf<ABibleProjectile> BibleProjectileClass;
};