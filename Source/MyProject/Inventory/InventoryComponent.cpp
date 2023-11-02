// Fill out your copyright notice in the Description page of Project Settings.


#include "../Inventory/InventoryComponent.h"

#include "../Weapon/WeaponBase.h"
#include "../Weapon/EquipmentBase.h"

#include "../ZombieSurvivalGameInstance.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInventoryComponent::TestAddFunction()
{
	if (AddWeapon(TestWeaponName) == false)
	{
		AddEquipment(TestWeaponName);
	}
}

bool UInventoryComponent::AddWeapon(FName WeaponName)
{
	UZombieSurvivalGameInstance* GameInstance = GetWorld()->GetGameInstance<UZombieSurvivalGameInstance>();
	if (GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::AddWeapon) GameInstance is not UZombieSurvivalGameInstance"));
		return false;
	}
	
	FWeaponData* WeaponData = GameInstance->GetWeaponData(WeaponName);

	if (WeaponData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::AddWeapon) Cannot Find Weapon Data From WeaponName"));
		return false;
	}

	AWeaponBase* TargetWeapon = nullptr;

	// Find Weapon Actor
	for (int i = 0; i < WeaponArray.Num(); ++i)
	{
		if (WeaponArray[i]->GetWeaponName() == WeaponName)
		{
			TargetWeapon = WeaponArray[i];
			break;
		}
	}

	if (TargetWeapon == nullptr)
	{
		// Add New Weapon
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AWeaponBase* Weapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponData->WeaponClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), Params);
		if (Weapon == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::AddWeapon) Failed to spawn Weapon"));
			return false;
		}
		Weapon->Attach(GetOwner());
		WeaponArray.Add(Weapon);
		if (Weapon->IsPossibleToLevelUp()) EnforcableNameSet.Add(Weapon->GetWeaponName());

		if (NewItemNameSet.Contains(WeaponName))
		{
			NewItemNameSet.Remove(NewItemNameSet.FindId(WeaponName));
		}
	}
	else
	{
		if (EnforcableNameSet.Contains(TargetWeapon->GetWeaponName()))
		{
			// Enforce Weapon
			TargetWeapon->LevelUp();

			if (TargetWeapon->IsPossibleToLevelUp() == false)
			{
				EnforcableNameSet.Remove(EnforcableNameSet.FindId(TargetWeapon->GetWeaponName()));
			}
		}
		else
		{
			// 강화 불가
			UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::AddWeapon) %s is already Max Level"), *TargetWeapon->GetWeaponName().ToString());
			return false;
		}
	}
	return true;
}

bool UInventoryComponent::AddEquipment(FName EquipmentName)
{
	UZombieSurvivalGameInstance* GameInstance = GetWorld()->GetGameInstance<UZombieSurvivalGameInstance>();
	if (GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::AddEquipment) GameInstance is not UZombieSurvivalGameInstance"));
		return false;
	}

	FEquipmentData* EquipmentData = GameInstance->GetEquipmentData(EquipmentName);

	if (EquipmentData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::AddEquipment) Cannot Find Weapon Data From WeaponName"));
		return false;
	}

	AEquipmentBase* TargetEquipment = nullptr;

	// Check Is Equipment Already In Array
	for (int i = 0; i < EquipmentArray.Num(); ++i)
	{
		if (EquipmentArray[i]->GetEquipmentName() == EquipmentName)
		{
			TargetEquipment = EquipmentArray[i];
			break;
		}
	}

	if (TargetEquipment == nullptr)
	{
		// Add New Equipment
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AEquipmentBase* Equipment = GetWorld()->SpawnActor<AEquipmentBase>(EquipmentData->EquipmentClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), Params);
		if (Equipment == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::AddEquipment) Failed to spawn Equipment"));
			return false;
		}
		Equipment->Attach(GetOwner());
		EquipmentArray.Add(Equipment);
		if (Equipment->IsEnforcable()) EnforcableNameSet.Add(Equipment->GetEquipmentName());

		if (NewItemNameSet.Contains(EquipmentName))
		{
			NewItemNameSet.Remove(NewItemNameSet.FindId(EquipmentName));
		}
	}
	else
	{
		if (EnforcableNameSet.Contains(TargetEquipment->GetEquipmentName()))
		{
			// Enforce Equipment
			TargetEquipment->LevelUp();

			if (TargetEquipment->IsEnforcable() == false)
			{
				EnforcableNameSet.Remove(EnforcableNameSet.FindId(TargetEquipment->GetEquipmentName()));
			}
		}
		else
		{
			// 강화 불가
			UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::AddEquipment) %s is already Max Level"), *TargetEquipment->GetEquipmentName().ToString());
			return false;
		}
	}

	return true;
}

void UInventoryComponent::GetEnforcableItemName(TArray<FName>& ItemNameArray, int32 ItemCount)
{
	TArray<FName> Array = EnforcableNameSet.Array();
	if (Array.Num() == 0)
	{
		for (int i = 0; i < ItemCount; ++i)
		{
			ItemNameArray.Add(TEXT("Money"));
		}
	}
	else
	{
		for (int i = 0; i < ItemCount; ++i)
		{
			ItemNameArray.Add(Array[FMath::RandRange(0, EnforcableNameSet.Num() - 1)]);
		}
	}
}

void UInventoryComponent::GetAddableItemName(TArray<FName>& ItemNameArray, int32 ItemCount)
{
	TArray<FName> Array = EnforcableNameSet.Array();
	// How To Get Addable Item Name List?

	Array += NewItemNameSet.Array();

	while (ItemNameArray.Num () < ItemCount)
	{
		if (Array.Num() > 0)
		{
			int32 Index = FMath::RandRange(0, Array.Num() - 1);
			ItemNameArray.Add(Array[Index]);
			Array.RemoveAt(Index);
		}
		else break;
	}
}

int UInventoryComponent::GetItemLevel(FName ItemName)
{
	for (int i = 0; i < WeaponArray.Num(); ++i)
	{
		if (WeaponArray[i]->GetWeaponName() == ItemName)
		{
			return WeaponArray[i]->GetCurrentLevel();
		}
	}

	// Todo : EqupimentArray Search

	return 0;
}