// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include <GameFramework/Actor.h>
#include "EquipmentBase.generated.h"

class UTexture2D;
USTRUCT()
struct FEquipmentData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText EquipmentName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* EquipmentImage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AEquipmentBase> EquipmentClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FText> DiscriptionTextArray;
};

class UStatusComponent;
UCLASS()
class MYPROJECT_API AEquipmentBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipmentBase();

	virtual void LevelUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Attach(AActor* OwningCharacter);
	virtual void Dettach();

	int32 GetCurrentLevel() const;
	int32 GetMaxLevel() const;

	bool IsEnforcable() const;

	FName GetEquipmentName() const;

protected:
	UPROPERTY(EditDefaultsOnly)
	FName EquipmentName;
	UPROPERTY(EditDefaultsOnly)
	int32 CurrentLevel = 1;
	UPROPERTY(EditDefaultsOnly)
	int32 MaxLevel;

	UPROPERTY(EditDefaultsOnly)
	UStatusComponent* StatusComponent;
};