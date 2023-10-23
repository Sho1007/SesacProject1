// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

class APoolingActor;
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

private:
	void SpawnEnemy();
	void PrepareEnemy();

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Spawn", Meta = (AllowPrivateAccess))
	float EnemySpawnCool;
	float CurrentEnemySpawnCool;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy Spawn", Meta = (AllowPrivateAccess))
	int EnemyPoolingCount;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = "Enemy Spawn", Meta = (AllowPrivateAccess))
	TArray<APoolingActor*> EnemyPool;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Enemy Spawn", Meta = (AllowPrivateAccess))
	TSubclassOf<APoolingActor> EnemyClass;
};