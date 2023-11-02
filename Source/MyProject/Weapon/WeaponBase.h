// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>
#include <Engine/DataTable.h>

#include <WeaponBase.generated.h>

class UTexture2D;
USTRUCT()
struct FWeaponData : public FTableRowBase
{
	GENERATED_BODY()

	public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText WeaponName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* WeaponImage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AWeaponBase> WeaponClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FText> DiscriptionTextArray;
};

class ASpawnManager;
class UStatusComponent;
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

	int GetCurrentLevel() const;
	int GetMaxLevel() const;

	FName GetWeaponName() const;

	virtual void Attach(AActor* OwningCharacter);

	virtual void LevelUp();

public:
	// bind
	UFUNCTION()
	virtual void UpdateAmount(int32 NewAmount);
	UFUNCTION()
	virtual void UpdateArea(float NewArea);
	UFUNCTION()
	virtual void UpdateSpeed(float NewSpeed);
	UFUNCTION()
	virtual void UpdateMight(float NewMight);
	UFUNCTION()
	virtual void UpdateDuration(float NewDuration);
	UFUNCTION()
	virtual void UpdateCooldown(float NewCooldown);

protected:
	// Weapon Information
	UPROPERTY(EditDefaultsOnly)
	FName WeaponName;
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* WeaponImage;

	// Level
	UPROPERTY(EditDefaultsOnly)
	int CurrentLevel = 1;
	UPROPERTY(EditDefaultsOnly)
	int MaxLevel;

	// WeaponStat
	UPROPERTY(EditDefaultsOnly)
	float WeaponDamage;
	UPROPERTY(EditDefaultsOnly)
	float WeaponSpeed;
	UPROPERTY(EditDefaultsOnly)
	float WeaponArea;
	UPROPERTY(EditDefaultsOnly)
	float WeaponDuration;
	UPROPERTY(EditDefaultsOnly)
	float CurrentWeaponDuration;
	UPROPERTY(EditDefaultsOnly)
	int32 WeaponPierce;
	UPROPERTY(EditDefaultsOnly)
	float WeaponKnockback;

	UPROPERTY(EditDefaultsOnly)
	float ProjectileSpeed;

	UPROPERTY(EditDefaultsOnly)
	int32 ProjectileCount;
	int32 CurrentProjectileCount;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	float ProjectileInterval = 0.1f;

	// CoolTime
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AttackCoolTime;
	float CurrentAttackCoolTime;

	// SpawnMaanger
	UPROPERTY(Meta = (AllowPrivateAccess))
	ASpawnManager* SpawnManager;
	UPROPERTY(Meta = (AllowPrivateAccess))
	UStatusComponent* StatusComponent;

	// From Status Component
	int32 StatusAmount;
	float StatusArea;
	float StatusSpeed;
	float StatusMight;
	float StatusDuration;
	float StatusCooldown;
};