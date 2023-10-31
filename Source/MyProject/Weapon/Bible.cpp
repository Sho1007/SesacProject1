// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/Bible.h"

#include <GameFramework/Character.h>

#include "BibleProjectile.h"
#include "MyProject/Character/StatusComponent.h"

void ABible::BeginPlay()
{
	Super::BeginPlay();
}

void ABible::AddProjectile(int AddCount)
{
	if (BibleProjectileClass)
	{
		for (int i = 0; i < AddCount; ++i)
		{
			ABibleProjectile* Projectile = GetWorld()->SpawnActor<ABibleProjectile>(BibleProjectileClass);

			Projectile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, false));
			Projectile->SetActorRelativeLocation(FVector(ProjectileDistance, 0, 0));

			ProjectileArray.Add(Projectile);
		}
	}

	for (int i = 0; i < ProjectileArray.Num(); ++i)
	{
		FVector RelativeLocation(ProjectileDistance, 0, 0);
		RelativeLocation = RelativeLocation.RotateAngleAxis((360 / ProjectileArray.Num()) * i, {0, 0, 1});
		ProjectileArray[i]->SetActorRelativeLocation(RelativeLocation);
	}

	Attack();
}

void ABible::Tick(float DeltaSeconds)
{
	Super::Super::Tick(DeltaSeconds);

	if (bIsAttacking)
	{
		CurrentWeaponDuration += DeltaSeconds;

		if (CurrentWeaponDuration >= WeaponDuration * (StatusComponent->GetDuration() / 100.0f))
		{
			bIsAttacking = false;
			CurrentWeaponDuration = 0.0f;
			for (int i = 0; i < ProjectileArray.Num(); ++i)
			{
				ProjectileArray[i]->Deactivate();
			}
		}
	}
	else
	{
		CurrentAttackCoolTime += DeltaSeconds;

		if (CurrentAttackCoolTime >= AttackCoolTime)
		{
			bIsAttacking = true;

			Attack();
		}
	}

	AddActorWorldRotation(FRotator(0, 1 * DeltaSeconds * RotateSpeed, 0));
}

void ABible::Attack()
{
	Super::Attack();
	UE_LOG(LogTemp, Warning, TEXT("ABible::Attack"));

	CurrentAttackCoolTime = 0.0f;

	for (int i = 0; i < ProjectileArray.Num(); ++i)
	{
		ProjectileArray[i]->Activate();
	}
}

void ABible::Attach(AActor* OwningCharacter)
{
	Super::Attach(OwningCharacter);

	if (ACharacter* Character = Cast<ACharacter>(OwningCharacter))
	{
		this->AttachToActor(Character, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}


	AddProjectile(ProjectileCount);
}

void ABible::LevelUp()
{
	Super::LevelUp();

	switch (CurrentLevel)
	{
	case 1:
		AddProjectile();
		break;
	case 2:
		AddProjectile();
		break;
	case 3:
		AddProjectile();
		break;
	}
}