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

				FName EquipmentName = EvolveRequireMap[WeaponName];

				for (int i = 0; i < EquipmentArray.Num(); ++i)
				{
					if (EquipmentArray[i]->GetEquipmentName() == EquipmentName && EquipmentArray[i]->IsEnforcable() == false)
					{
						EvolvableNameArray.Add(EvolveWeaponMap[WeaponName]);
						break;
					}
				}
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

				FName WeaponName = EvolveRequireMap[EquipmentName];

				for (int i = 0; i < WeaponArray.Num(); ++i)
				{
					if (WeaponArray[i]->GetWeaponName() == WeaponName && WeaponArray[i]->IsPossibleToLevelUp() == false)
					{
						EvolvableNameArray.Add(EvolveWeaponMap[WeaponName]);
						break;
					}
				}
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

bool UInventoryComponent::AddItem(FName ItemName)
{
	if (ItemName == TEXT("Money"))
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::AddItem) Add Money"));
		return true;
	}
	else if (ItemName == TEXT("Meal"))
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::AddItem) Eat Meal"));
		return true;
	}

	return false;
}

void UInventoryComponent::GetEnforcableItemName(TArray<FName>& ItemNameArray, int32 ItemCount)
{
	while (EvolvableNameArray.IsEmpty() == false)
	{
		ItemNameArray.Add(EvolvableNameArray[0]);
		EvolvableNameArray.RemoveAt(0);

		if (ItemNameArray.Num() == ItemCount) break;
	}

	TArray<FName> Array = EnforcableNameSet.Array();

	if (Array.Num() == 0)
	{
		while (ItemNameArray.Num() < ItemCount)
		{
			ItemNameArray.Add(TEXT("Money"));
		}
	}
	else
	{
		while (ItemNameArray.Num() < ItemCount)
		{
			ItemNameArray.Add(Array[FMath::RandRange(0, EnforcableNameSet.Num() - 1)]);
		}
	}
}

void UInventoryComponent::GetAddableItemName(TArray<FName>& ItemNameArray, int32 ItemCount, bool bIsLevelUp)
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
		else
		{
			ItemNameArray.Add("Meal");
			if (ItemNameArray.Num() == ItemCount) break;
			ItemNameArray.Add("Money");
			break;
		}
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

	for (int i = 0; i < EquipmentArray.Num(); ++i)
	{
		if (EquipmentArray[i]->GetEquipmentName() == ItemName)
		{
			return EquipmentArray[i]->GetCurrentLevel();
		}
	}

	return 0;
}

void UInventoryComponent::RemoveIngredient(FName EvolvedWeaponName)
{
	FName WeaponName;
	for (auto Iter : EvolveWeaponMap)
	{
		if (Iter.Value == EvolvedWeaponName)
		{
			WeaponName = Iter.Key;
			break;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::RemoveIngredient) Remove Weapon %s"), *WeaponName.ToString());

	for (int i = 0; i < WeaponArray.Num(); ++i)
	{
		if (WeaponArray[i]->GetWeaponName() == WeaponName)
		{
			AWeaponBase* DeleteWeapon = WeaponArray[i];
			WeaponArray.RemoveAt(i);
			DeleteWeapon->Destroy();
			break;
		}
	}
}