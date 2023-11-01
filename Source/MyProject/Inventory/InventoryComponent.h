// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AWeaponBase;
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

	void GetEnforcableItemName(TArray<FName>& ItemNameArray, int32 ItemCount);

	void GetAddableItemName(TArray<FName>& ItemNameArray, int32 ItemCount);

	int GetItemLevel(FName ItemName);
private:
	UPROPERTY(VisibleInstanceOnly, Category = "Inventory Component", Meta = (AllowPrivateAccess))
	TArray<AWeaponBase*> WeaponArray;
	UPROPERTY(VisibleInstanceOnly, Category = "Inventory Component", Meta = (AllowPrivateAccess))
	TSet<FName> EnforcableNameSet;
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Component", Meta = (AllowPrivateAccess))
	TSet<FName> NewItemNameSet;
};