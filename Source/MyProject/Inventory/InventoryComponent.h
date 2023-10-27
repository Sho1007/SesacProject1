// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include <Engine/DataTable.h>

#include "InventoryComponent.generated.h"

class AWeaponBase;
USTRUCT()
struct FWeaponData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AWeaponBase> WeaponClass;
};

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
	
	bool AddWeapon(FName WeaponName);
private:
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Component", Meta = (AllowPrivateAccess))
	UDataTable* WeaponDataTable;
	UPROPERTY(VisibleInstanceOnly, Category = "Inventory Component", Meta = (AllowPrivateAccess))
	TArray<AWeaponBase*> WeaponArray;
	UPROPERTY(VisibleInstanceOnly, Category = "Inventory Component", Meta = (AllowPrivateAccess))
	TSet<FName> EnforcableNameSet;
};