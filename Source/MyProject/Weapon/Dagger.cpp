// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/Dagger.h"

#include "EngineUtils.h"
#include "GameFramework/Character.h"
#include "MyProject/ObjectPooling/SpawnManager.h"

void ADagger::Init(ASpawnManager* NewSpawnManager)
{
	SpawnManager = NewSpawnManager;
}

void ADagger::SpawnDagger()
{
	if (SpawnManager)
	{
		SpawnManager->SpawnProjectile(GetActorLocation() + FVector(0, FMath::RandRange(-75.0f, 75.0f), 90), GetActorRotation(), TEXT("Dagger"));
	}

	if (--CurrentProjectileCount == 0) GetWorld()->GetTimerManager().ClearTimer(AttackHandle);
}

void ADagger::Attach(AActor* OwningCharacter)
{
	Super::Attach(OwningCharacter);

	if (ACharacter* Character = Cast<ACharacter>(OwningCharacter))
	{
		this->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		this->SetActorRelativeLocation(FVector(0, 0, 90));
		this->SetActorRelativeRotation(FRotator(0, 90, 0));

		TActorIterator<AActor> It(GetWorld(), ASpawnManager::StaticClass());
		SpawnManager = Cast<ASpawnManager>(*It);

		if (SpawnManager == false)
		{
			UE_LOG(LogTemp, Error, TEXT("ADagger::Attach) SpawnManager is nullptr"));
		}
	}
}

void ADagger::Attack()
{
	Super::Attack();

	if (AttackHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(AttackHandle);

	if (ProjectileCount == 0) return;

	CurrentProjectileCount = ProjectileCount;
	GetWorld()->GetTimerManager().SetTimer(AttackHandle, this, &ADagger::SpawnDagger, ThrowInterval, true);
}
