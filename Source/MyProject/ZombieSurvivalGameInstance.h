// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ZombieSurvivalGameInstance.generated.h"

/**
 * 
 */
class UZombieSurvivalSaveGame;
class UDataTable;
struct FWeaponData;
struct FEquipmentData;
struct FProjectileData;
struct FItemData;
UCLASS()
class MYPROJECT_API UZombieSurvivalGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UZombieSurvivalSaveGame* GetSaveGame();
	FWeaponData* GetWeaponData(FName WeaponName) const;
	FEquipmentData* GetEquipmentData(FName EquipmentName) const;
	FProjectileData* GetProjectileData(FName ProjectileName) const;
	FItemData* GetItemData(FName ItemName) const;
private:
	// Save Game
	UZombieSurvivalSaveGame* SaveGameInstance;
	// Data Table
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	UDataTable* WeaponDataTable;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	UDataTable* EquipmentDataTable;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	UDataTable* ProjectileDataTable;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	UDataTable* ItemDataTable;
};