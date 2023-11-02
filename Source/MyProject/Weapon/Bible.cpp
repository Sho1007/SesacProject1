// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/Bible.h"

#include <GameFramework/Character.h>

#include "BibleProjectile.h"
#include "MyProject/Character/StatusComponent.h"

void ABible::BeginPlay()
{
	Super::BeginPlay();
}

void ABible::AddProjectile()
{
	if (BibleProjectileClass)
	{
		for (int i = 0; i < ProjectileArray.Num(); ++i)
		{
			ProjectileArray[i]->Destroy();
		}

		ProjectileArray.Empty();

		for (int i = 0; i < ProjectileCount + StatusAmount; ++i)
		{
			ABibleProjectile* Projectile = GetWorld()->SpawnActor<ABibleProjectile>(BibleProjectileClass);
			Projectile->Deactivate();

			Projectile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false));

			ProjectileArray.Add(Projectile);
		}

		SetAreaAndRotation();

		Attack();
	}
}

void ABible::Tick(float DeltaSeconds)
{
	Super::Super::Tick(DeltaSeconds);

	if (bIsAttacking)
	{
		CurrentWeaponDuration += DeltaSeconds;

		if (CurrentWeaponDuration >= WeaponDuration * StatusDuration)
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

		if (CurrentAttackCoolTime >= AttackCoolTime - (AttackCoolTime * StatusCooldown))
		{
			bIsAttacking = true;

			Attack();
		}
	}

	AddActorWorldRotation(FRotator(0, DeltaSeconds * BaseSpeed * WeaponSpeed * StatusSpeed, 0));
}

void ABible::Attack()
{
	Super::Attack();
	UE_LOG(LogTemp, Warning, TEXT("ABible::Attack"));

	CurrentAttackCoolTime = 0.0f;

	for (int i = 0; i < ProjectileArray.Num(); ++i)
	{
		ProjectileArray[i]->SetProjectileData(nullptr, 0, WeaponDamage * StatusMight, -1, WeaponArea * StatusArea, WeaponKnockback);
		ProjectileArray[i]->Activate();
	}
}

void ABible::Attach(AActor* OwningCharacter)
{
	Super::Attach(OwningCharacter);

	if (ACharacter* Character = Cast<ACharacter>(OwningCharacter))
	{
		this->AttachToActor(Character, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false));
	}

	AddProjectile();
}

void ABible::LevelUp()
{
	Super::LevelUp();

	switch (CurrentLevel)
	{
	case 2:
		ProjectileCount++;
		AddProjectile();
		break;
	case 3:
		WeaponArea += 0.25f;
		WeaponSpeed += 0.3f;
		break;
	case 4:
		WeaponDamage += 10.0f;
		WeaponDuration += 0.5f;
		break;
	case 5:
		ProjectileCount++;
		AddProjectile();
		break;
	case 6:
		WeaponArea += 0.25f;
		WeaponSpeed += 0.3f;
		break;
	case 7:
		WeaponDuration += 0.5f;
		WeaponDamage += 10.0f;
	case 8:
		ProjectileCount++;
		AddProjectile();
	}
}

void ABible::UpdateArea(float NewArea)
{
	Super::UpdateArea(NewArea);
	SetAreaAndRotation();
}

void ABible::UpdateAmount(int32 NewAmount)
{
	Super::UpdateAmount(NewAmount);

	AddProjectile();
}

void ABible::SetAreaAndRotation()
{
	for (int i = 0; i < ProjectileArray.Num(); ++i)
	{
		FVector RelativeLocation(BaseArea * WeaponArea * StatusArea, 0, 0);
		RelativeLocation = RelativeLocation.RotateAngleAxis((360 / ProjectileArray.Num()) * i, { 0, 0, 1 });
		ProjectileArray[i]->SetActorRelativeLocation(RelativeLocation);
	}
}
