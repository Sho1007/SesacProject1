// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/Dagger.h"

#include "MyProject/ObjectPooling/SpawnManager.h"

void ADagger::Init(ASpawnManager* NewSpawnManager)
{
	SpawnManager = NewSpawnManager;
}

void ADagger::SpawnDagger()
{
	UE_LOG(LogTemp, Warning, TEXT("ADagger::SpawnDagger : %d"), CurrentProjectileCount);
	if (SpawnManager) SpawnManager->SpawnProjectile(GetActorLocation() + FVector(0, FMath::RandRange(-75.0f, 75.0f), 90), GetActorRotation(), TEXT("Dagger"));

	if (--CurrentProjectileCount == 0) GetWorld()->GetTimerManager().ClearTimer(AttackHandle);
}

void ADagger::Attack()
{
	Super::Attack();

	if (AttackHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(AttackHandle);

	CurrentProjectileCount = ProjectileCount;

	GetWorld()->GetTimerManager().SetTimer(AttackHandle, this, &ADagger::SpawnDagger, ThrowInterval, true);
}