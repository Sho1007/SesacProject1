// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Weapon/WeaponBase.h"
#include "Dagger.generated.h"

/**
 * 
 */
class ASpawnManager;
UCLASS()
class MYPROJECT_API ADagger : public AWeaponBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Init(ASpawnManager* NewSpawnManager);

	void SpawnDagger();

	virtual void Attach(AActor* OwningCharacter) override;


protected:
	virtual void Attack() override;

	virtual void LevelUp() override;

private:

	FTimerHandle AttackHandle;
};