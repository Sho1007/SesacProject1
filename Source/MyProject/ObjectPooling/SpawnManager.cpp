// Fill out your copyright notice in the Description page of Project Settings.


#include "../ObjectPooling/SpawnManager.h"

#include "PoolingActor.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	PrepareEnemy();
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Enemy Spawn Cool
	CurrentEnemySpawnCool += DeltaTime;
	if (CurrentEnemySpawnCool >= EnemySpawnCool)
	{
		CurrentEnemySpawnCool = 0.0f;
		SpawnEnemy();
	}
}

void ASpawnManager::SpawnEnemy()
{
	for (int i = 0; i < EnemyPool.Num(); ++i)
	{
		//if ()
	}
}

void ASpawnManager::PrepareEnemy()
{
	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASpawnManager::PrepareMonster) World is nullptr"));
		return;
	}
	if (EnemyClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASpawnManager::PrepareMonster) EnemyClass is nullptr"));
		return;
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int i = 0; i < EnemyPoolingCount; ++i)
	{
		APoolingActor* Enemy = World->SpawnActor<APoolingActor>(EnemyClass, Params);
		Enemy->Deactivate();
		EnemyPool.Add(Enemy);
	}
}
