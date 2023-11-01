// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquipmentBase.generated.h"

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

protected:
	UPROPERTY(EditDefaultsOnly)
	int32 CurrentLevel = 1;
	UPROPERTY(EditDefaultsOnly)
	int32 MaxLevel;

	UPROPERTY(EditDefaultsOnly)
	UStatusComponent* StatusComponent;
};