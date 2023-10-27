// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"


class UTexture2D;
UCLASS()
class MYPROJECT_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	virtual void Attack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsPossibleToLevelUp() const;

protected:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* WeaponImage;
	UPROPERTY(EditDefaultsOnly)
	int CurrentLevel;
	UPROPERTY(EditDefaultsOnly)
	int MaxLevel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AttackCoolTime;
	float CurrentAttackCoolTime;
};