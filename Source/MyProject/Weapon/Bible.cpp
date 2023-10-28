// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/Bible.h"

#include <GameFramework/Character.h>

#include "BibleProjectile.h"

void ABible::BeginPlay()
{
	Super::BeginPlay();

	AddProjectile(9);
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
		ProjectileArray[i]->SetDuration(Duration);
		ProjectileArray[i]->Activate();
	}
	CurrentAttackCoolTime = 0.0f;
}

void ABible::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AddActorWorldRotation(FRotator(0, 1 * DeltaSeconds * RotateSpeed, 0));
}

void ABible::Attack()
{
	Super::Attack();

	UE_LOG(LogTemp, Warning, TEXT("ABible::Attack"));

	for (int i = 0; i < ProjectileArray.Num(); ++i)
	{
		ProjectileArray[i]->SetDuration(Duration);
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
}