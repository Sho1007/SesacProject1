// Fill out your copyright notice in the Description page of Project Settings.


#include "../Inventory/InventoryComponent.h"

#include "../Weapon/WeaponBase.h"

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
	AddWeapon(TestWeaponName);
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
		EnforcableNameSet.Add(Weapon->GetWeaponName());
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
			UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::AddWeapon"));
			return false;
		}
	}

	return true;
}

void UInventoryComponent::GetEnforcableItemName(TArray<FName>& ItemNameArray, int32 ItemCount)
{
	TArray<FName> Array = EnforcableNameSet.Array();
	for (int i = 0; i < ItemCount; ++i)
	{
		ItemNameArray.Add(Array[FMath::RandRange(0, EnforcableNameSet.Num() - 1)]);
	}
}