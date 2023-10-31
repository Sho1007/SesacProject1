// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class ASpawnManager;
class UStatusComponent;
class UTexture2D;
UCLASS()
class MYPROJECT_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	virtual void Attack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsPossibleToLevelUp() const;

	int GetCurrentLevel() const;
	int GetMaxLevel() const;

	FName GetWeaponName() const;

	virtual void Attach(AActor* OwningCharacter);

	virtual void LevelUp();

protected:
	// Weapon Information
	UPROPERTY(EditDefaultsOnly)
	FName WeaponName;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* WeaponImage;

	// Level
	UPROPERTY(EditDefaultsOnly)
	int CurrentLevel;
	UPROPERTY(EditDefaultsOnly)
	int MaxLevel;

	// WeaponStat
	UPROPERTY(EditDefaultsOnly)
	float WeaponDamage;
	UPROPERTY(EditDefaultsOnly)
	float WeaponArea;
	UPROPERTY(EditDefaultsOnly)
	float WeaponDuration;
	UPROPERTY(EditDefaultsOnly)
	float CurrentWeaponDuration;
	UPROPERTY(EditDefaultsOnly)
	int32 WeaponPierce;

	UPROPERTY(EditDefaultsOnly)
	float ProjectileSpeed;

	UPROPERTY(EditDefaultsOnly)
	int32 ProjectileCount;
	int32 CurrentProjectileCount;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	float ProjectileInterval = 0.1f;

	// CoolTime
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AttackCoolTime;
	float CurrentAttackCoolTime;

	// SpawnMaanger
	UPROPERTY(Meta = (AllowPrivateAccess))
	ASpawnManager* SpawnManager;
	UPROPERTY(Meta = (AllowPrivateAccess))
	UStatusComponent* StatusComponent;
};