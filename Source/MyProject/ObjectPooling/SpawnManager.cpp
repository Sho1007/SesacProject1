// Fill out your copyright notice in the Description page of Project Settings.


#include "../ObjectPooling/SpawnManager.h"

#include <EngineUtils.h>
#include <Engine/DataTable.h>
#include "PoolingActor.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include "MyProject/Character/EnemyBase.h"
#include "ProjectileBase.h"

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
	PrepareProjectile();
	PrepareBoss();
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

	// Boss Spawn Cool
	CurrentBossSpawnCool += DeltaTime;
	if (CurrentBossSpawnCool >= BossSpawnCool)
	{
		CurrentBossSpawnCool -= BossSpawnCool;
		SpawnBoss();
	}
}

void ASpawnManager::RespawnEnemy(int32 PoolingIndex)
{
	if (PoolingIndex < 0 || PoolingIndex >= EnemyPool.Num()) return;

	EnemyPool[PoolingIndex]->SetActorLocation(GetSpawnLocation());
}

void ASpawnManager::RespawnBoss(int32 PoolingIndex)
{
	if (PoolingIndex < 0 || PoolingIndex >= BossPool.Num()) return;

	BossPool[PoolingIndex]->SetActorLocation(GetSpawnLocation() + FVector(0, 0, 100));
}

void ASpawnManager::SpawnProjectile(FVector StartLocation, FRotator StartRotation, FName ProjectileName)
{
	for (int i = 0; i < ProjectilePool.Num(); ++i)
	{
		if (ProjectilePool[i]->IsActive() == false)
		{
			// Find Projectile Information From DataTable
			Cast<AProjectileBase>(ProjectilePool[i])->SetProjectileData(ProjectileDataTable->FindRow<FProjectileData>(ProjectileName, ""));
			ProjectilePool[i]->SetActorLocationAndRotation(StartLocation, StartRotation);
			ProjectilePool[i]->Activate();
			break;
		}
	}
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

	//UE_LOG(LogTemp, Error, TEXT("ASpawnManager::SpawnJewel) EnemyCount is not enough"));
}

void ASpawnManager::PrepareEnemy()
{
	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ASpawnManager::PrepareMonster) World is nullptr"));
		return;
	}
	if (EnemyClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ASpawnManager::PrepareMonster) EnemyClass is nullptr"));
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

void ASpawnManager::PrepareProjectile()
{
	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ASpawnManager::PrepareProjectile) World is nullptr"));
		return;
	}
	if (ProjectileClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ASpawnManager::PrepareProjectile) ProjectileClass is nullptr"));
		return;
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int i = 0; i < ProjectilePoolingCount; ++i)
	{
		APoolingActor* Projectile = World->SpawnActor<APoolingActor>(ProjectileClass, Params);
		Projectile->Deactivate();
		ProjectilePool.Add(Projectile);
	}
}

void ASpawnManager::SpawnBoss()
{
	for (int i = 0; i < BossPool.Num(); ++i)
	{
		if (BossPool[i]->IsActive() == false)
		{
			BossPool[i]->SetActorLocation(GetSpawnLocation() + FVector(0, 0, 100));
			BossPool[i]->Activate();
			return;
		}
	}
}

void ASpawnManager::PrepareBoss()
{
	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ASpawnManager::PrepareBoss) World is nullptr"));
		return;
	}
	if (BossClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ASpawnManager::PrepareBoss) BossClass is nullptr"));
		return;
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int i = 0; i < BossPoolingCount; ++i)
	{
		APoolingActor* Boss = World->SpawnActor<APoolingActor>(BossClass, Params);
		if (AEnemyBase* EnemyBase = Cast<AEnemyBase>(Boss)) EnemyBase->Init(this, i);
		Boss->Deactivate();
		BossPool.Add(Boss);
	}
}

FVector ASpawnManager::GetSpawnLocation()
{
	if (TargetCharacter == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASpawnManager::GetSpawnLocation) TargetCharacter is nullptr"));
		return FVector::ZeroVector;
	}

	FVector SpawnLocation = TargetCharacter->GetActorLocation();
	SpawnLocation.Z = 100.0f;

	FVector Velocity = TargetCharacter->GetVelocity();
	if (Velocity == FVector::ZeroVector)
	{
		//UE_LOG(LogTemp, Warning, TEXT("ASpawnManager::GetSpawnLocation) Velocity : %s"), *Velocity.ToString());
		Velocity = TargetCharacter->GetActorForwardVector() * SpawnDistance;
		Velocity = Velocity.RotateAngleAxis(FMath::RandRange(-180.0f, 180.0f), { 0, 0, 1 });
		SpawnLocation += Velocity;
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
