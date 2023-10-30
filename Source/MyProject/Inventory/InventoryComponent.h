// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include <Engine/DataTable.h>

#include "InventoryComponent.generated.h"

class AWeaponBase;
class UTexture2D;
USTRUCT()
struct FWeaponData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* WeaponImage;
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

	UFUNCTION(BlueprintCallable)
	bool AddWeapon(FName WeaponName);

	void GetEnforcableItemName(TArray<FName>& ItemNameArray, int32 ItemCount);
private:
	UPROPERTY(VisibleInstanceOnly, Category = "Inventory Component", Meta = (AllowPrivateAccess))
	TArray<AWeaponBase*> WeaponArray;
	UPROPERTY(VisibleInstanceOnly, Category = "Inventory Component", Meta = (AllowPrivateAccess))
	TSet<FName> EnforcableNameSet;
};