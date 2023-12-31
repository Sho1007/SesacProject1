// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieSurvivalGameInstance.h"

#include <Kismet/GameplayStatics.h>

#include "ObjectPooling/ProjectileBase.h"
#include "Weapon/WeaponBase.h"
#include "Weapon/EquipmentBase.h"
#include "ObjectPooling/ItemBase.h"
#include "SaveGame/ZombieSurvivalSaveGame.h"

UZombieSurvivalSaveGame* UZombieSurvivalGameInstance::GetSaveGame()
{
	if (SaveGameInstance == nullptr)
	{
		SaveGameInstance = Cast<UZombieSurvivalSaveGame>(UGameplayStatics::CreateSaveGameObject(UZombieSurvivalSaveGame::StaticClass()));
		SaveGameInstance = Cast<UZombieSurvivalSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameInstance->GetSaveSlotName(), SaveGameInstance->GetUserIndex()));
	}

	return SaveGameInstance;
}

FWeaponData* UZombieSurvivalGameInstance::GetWeaponData(FName WeaponName) const
{
	if (WeaponDataTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UZombieSurvivalGameInstance::GetWeaponData) WeaponDataTable is nullptr"));
		return nullptr;
	}

	return WeaponDataTable->FindRow<FWeaponData>(WeaponName, "");
}

FEquipmentData* UZombieSurvivalGameInstance::GetEquipmentData(FName EquipmentName) const
{
	if (EquipmentDataTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UZombieSurvivalGameInstance::GetWeaponData) EquipmentDataTable is nullptr"));
		return nullptr;
	}

	return EquipmentDataTable->FindRow<FEquipmentData>(EquipmentName, "");
}

FProjectileData* UZombieSurvivalGameInstance::GetProjectileData(FName ProjectileName) const
{
	if (ProjectileDataTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UZombieSurvivalGameInstance::GetProjectileData) ProjectileDataTable is nullptr"));
		return nullptr;
	}

	return ProjectileDataTable->FindRow<FProjectileData>(ProjectileName, "");
}

FItemData* UZombieSurvivalGameInstance::GetItemData(FName ItemName) const
{
	if (ItemDataTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UZombieSurvivalGameInstance::GetItemData) ItemDataTable is nullptr"));
		return nullptr;
	}

	return ItemDataTable->FindRow<FItemData>(ItemName, "");
}