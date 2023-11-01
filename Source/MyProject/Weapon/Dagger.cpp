// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/Dagger.h"

#include "GameFramework/Character.h"
#include "MyProject/Character/StatusComponent.h"
#include "MyProject/ObjectPooling/SpawnManager.h"

void ADagger::Init(ASpawnManager* NewSpawnManager)
{
	SpawnManager = NewSpawnManager;
}

void ADagger::SpawnDagger()
{
	if (SpawnManager && StatusComponent)
	{
		SpawnManager->SpawnProjectile(GetActorLocation() + FVector(0, 0, 45), GetActorRotation(), TEXT("Dagger"),
			ProjectileSpeed * (StatusComponent->GetSpeed() / 100.0f),
			WeaponDamage * (StatusComponent->GetMight() / 100.0f),
			WeaponPierce,
			WeaponArea * (StatusComponent->GetArea() / 100.0f),
			WeaponKnockback);
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
	}
}

void ADagger::Attack()
{
	Super::Attack();

	if (AttackHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(AttackHandle);

	if (ProjectileCount == 0) return;

	CurrentProjectileCount = ProjectileCount + StatusComponent->GetAmount();
	GetWorld()->GetTimerManager().SetTimer(AttackHandle, this, &ADagger::SpawnDagger, ProjectileInterval, true);
}

void ADagger::LevelUp()
{
	Super::LevelUp();

	switch(CurrentLevel)
	{
	case 2:
		ProjectileCount++;
		break;
	case 3:
		ProjectileCount++;
		WeaponDamage += 5;
		break;
	case 4:
		ProjectileCount++;
		break;
	case 5:
		WeaponPierce++;
		break;
	case 6:
		ProjectileCount++;
		break;
	case 7:
		ProjectileCount++;
		WeaponDamage += 5;
		break;
	case 8:
		WeaponPierce++;
		break;
	}
}