// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieSurvivalGameInstance.h"

#include "ObjectPooling/ProjectileBase.h"
#include "Inventory/InventoryComponent.h"

FWeaponData* UZombieSurvivalGameInstance::GetWeaponData(FName WeaponName) const
{
	if (WeaponDataTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UZombieSurvivalGameInstance::GetWeaponData) WeaponDataTable is nullptr"));
		return nullptr;
	}

	return WeaponDataTable->FindRow<FWeaponData>(WeaponName, "");
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