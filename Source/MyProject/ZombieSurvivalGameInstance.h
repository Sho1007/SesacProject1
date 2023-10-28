// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ZombieSurvivalGameInstance.generated.h"

/**
 * 
 */
class UDataTable;
struct FWeaponData;
struct FProjectileData;
UCLASS()
class MYPROJECT_API UZombieSurvivalGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FWeaponData* GetWeaponData(FName WeaponName) const;
	FProjectileData* GetProjectileData(FName ProjectileName) const;
private:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	UDataTable* WeaponDataTable;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	UDataTable* ProjectileDataTable;
};