// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

class APoolingActor;
class UDataTable;
UCLASS()
class MYPROJECT_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame	
	virtual void Tick(float DeltaTime) override;

	void RespawnEnemy(int32 PoolingIndex);
	void RespawnBoss(int32 PoolingIndex);

	void SpawnProjectile(FVector StartLocation, FRotator StartRotation, FName ProjectileName);

public:
	// Getter / Setter
	ACharacter* GetTargetCharacter() const;

private:
	void SpawnEnemy();
	void PrepareEnemy();

	void PrepareProjectile();

	void SpawnBoss();
	void PrepareBoss();

	FVector GetSpawnLocation();

private:
	// Data Table
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Spawn Manager", Meta = (AllowPrivateAccess))
	UDataTable* ProjectileDataTable;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Spawn Manager", Meta = (AllowPrivateAccess))
	ACharacter* TargetCharacter;

	// Enemy Spawn
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Spawn", Meta = (AllowPrivateAccess))
	float SpawnDistance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Spawn", Meta = (AllowPrivateAccess))
	float EnemySpawnCool;
	float CurrentEnemySpawnCool;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Spawn", Meta = (AllowPrivateAccess))
	int EnemyPoolingCount;
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Enemy Spawn", Meta = (AllowPrivateAccess))
	TArray<APoolingActor*> EnemyPool;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Enemy Spawn", Meta = (AllowPrivateAccess))
	TSubclassOf<APoolingActor> EnemyClass;

	// Projectile Spawn
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile Spawn", Meta = (AllowPrivateAccess))
	int ProjectilePoolingCount;
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Projectile Spawn", Meta = (AllowPrivateAccess))
	TArray<APoolingActor*> ProjectilePool;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Projectile Spawn", Meta = (AllowPrivateAccess))
	TSubclassOf<APoolingActor> ProjectileClass;

	// Boss Spawn
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Boss Spawn", Meta = (AllowPrivateAccess))
	int BossPoolingCount;
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Boss Spawn", Meta = (AllowPrivateAccess))
	TArray<APoolingActor*> BossPool;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Boss Spawn", Meta = (AllowPrivateAccess))
	TSubclassOf<APoolingActor> BossClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Boss Spawn", Meta = (AllowPrivateAccess))
	float BossSpawnCool;
	float CurrentBossSpawnCool;
};