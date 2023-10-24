// Fill out your copyright notice in the Description page of Project Settings.


#include "../ObjectPooling/SpawnManager.h"

#include <EngineUtils.h>
#include "PoolingActor.h"
#include "GameFramework/Character.h"
#include "MyProject/Character/EnemyBase.h"

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

	TActorIterator<AActor> It(GetWorld(), ACharacter::StaticClass());
	if (It)
	{
		TargetCharacter = Cast<ACharacter>(*It);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ASpawnManager::BeginPlay) No Player"));
	}

	PrepareEnemy();
	PrepareJewel();
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

void ASpawnManager::RespawnEnemy(int32 PoolingIndex)
{
	if (PoolingIndex < 0 || PoolingIndex >= EnemyPool.Num()) return;

	EnemyPool[PoolingIndex]->SetActorLocation(GetSpawnLocation());
}

void ASpawnManager::SpawnJewel(FVector SpawnLocation)
{
	//UE_LOG(LogTemp, Warning, TEXT("ASpawnManager::SpawnJewel"));
	for (int i = 0; i < JewelPool.Num(); ++i)
	{
		if (JewelPool[i]->IsActive() == false)
		{
			JewelPool[i]->SetActorLocation(SpawnLocation);
			JewelPool[i]->Activate();
			return;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("ASpawnManager::SpawnJewel) JewelCount is not enough"));
}

ACharacter* ASpawnManager::GetTargetCharacter() const
{
	return TargetCharacter;
}

void ASpawnManager::SpawnEnemy()
{
	//UE_LOG(LogTemp, Warning, TEXT("ASpawnManager::SpawnEnemy"));
	for (int i = 0; i < EnemyPool.Num(); ++i)
	{
		if (EnemyPool[i]->IsActive() == false)
		{
			EnemyPool[i]->SetActorLocation(GetSpawnLocation());
			EnemyPool[i]->Activate();
			return;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("ASpawnManager::SpawnJewel) EnemyCount is not enough"));
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
		if (AEnemyBase* EnemyBase = Cast<AEnemyBase>(Enemy)) EnemyBase->Init(this, i);
		EnemyPool.Add(Enemy);
	}
}

void ASpawnManager::PrepareJewel()
{
	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASpawnManager::PrepareJewel) World is nullptr"));
		return;
	}
	if (JewelClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASpawnManager::PrepareJewel) JewelClass is nullptr"));
		return;
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int i = 0; i < JewelPoolingCount; ++i)
	{
		APoolingActor* Jewel = World->SpawnActor<APoolingActor>(JewelClass, Params);
		Jewel->Deactivate();
		JewelPool.Add(Jewel);
	}
}

FVector ASpawnManager::GetSpawnLocation()
{
	FVector SpawnLocation = TargetCharacter->GetActorLocation();

	FVector Velocity = TargetCharacter->GetVelocity();
	if (Velocity == FVector::ZeroVector)
	{
		SpawnLocation += TargetCharacter->GetActorForwardVector() * SpawnDistance;
		SpawnLocation = SpawnLocation.RotateAngleAxis(FMath::RandRange(-180.0f, 180.0f), { 0, 0, 1 });
	}
	else
	{
		Velocity.Normalize();
		Velocity = Velocity.RotateAngleAxis(FMath::RandRange(-90.0f, 90.0f), { 0, 0, 1 });
		SpawnLocation += Velocity * SpawnDistance;
	}

	//UE_LOG(LogTemp, Warning, TEXT("ASpawnManager::GetSpawnLocation) SpawnLocation "));

	return SpawnLocation;
}