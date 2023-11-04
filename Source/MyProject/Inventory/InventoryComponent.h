// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AWeaponBase;
class AEquipmentBase;
UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	FName TestWeaponName;
	UFUNCTION(CallInEditor)
	void TestAddFunction();

	UFUNCTION(BlueprintCallable)
	bool AddWeapon(FName WeaponName);

	UFUNCTION(BlueprintCallable)
	bool AddEquipment(FName EquipmentName);

	UFUNCTION(BlueprintCallable)
	bool AddItem(FName ItemName);

	void GetEnforcableItemName(TArray<FName>& ItemNameArray, int32 ItemCount);

	void GetAddableItemName(TArray<FName>& ItemNameArray, int32 ItemCount, bool bIsLevelUp);

	int GetItemLevel(FName ItemName);

	void RemoveIngredient(FName EvolvedWeaponName);

public:
	// Getter
	const TArray<AWeaponBase*>& GetWeaponArray() const;
	const TArray<AEquipmentBase*>& GetEquipmentArray() const;

private:
	UPROPERTY(VisibleInstanceOnly, Category = "Inventory Component", Meta = (AllowPrivateAccess))
	TArray<AWeaponBase*> WeaponArray;
	UPROPERTY(VisibleInstanceOnly, Category = "Inventory Component", Meta = (AllowPrivateAccess))
	TArray<AEquipmentBase*> EquipmentArray;

	// 강화 가능한 무기 / 장비 이름 셋
	UPROPERTY(VisibleInstanceOnly, Category = "Inventory Component", Meta = (AllowPrivateAccess))
	TSet<FName> EnforcableNameSet;
	// 진화 가능한 무기 이름 배열
	UPROPERTY(VisibleInstanceOnly, Category = "Inventory Component", Meta = (AllowPrivateAccess))
	TArray<FName> EvolvableNameArray;

	// 진화에 필요한 무기 -> 장비 / 장비 -> 무기 이름 맵
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Component", Meta = (AllowPrivateAccess))
	TMap<FName, FName> EvolveRequireMap;
	// 무기 -> 진화된 무기 이름 맵
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Component", Meta = (AllowPrivateAccess))
	TMap<FName, FName> EvolveWeaponMap;

	// 아직 얻짐 못한 무기 / 장비 이름 셋
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Component", Meta = (AllowPrivateAccess))
	TSet<FName> NewItemNameSet;

public:
	// Delegate

	DECLARE_DELEGATE(FDele_Single);
	FDele_Single OnInventoryUpdated;
};