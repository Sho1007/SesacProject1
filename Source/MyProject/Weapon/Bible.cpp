// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/Bible.h"

#include "../ObjectPooling/ProjectileBase.h"

void ABible::AddProjectile()
{
	if (BibleProjectileClass)
	{
		AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(BibleProjectileClass);

		Projectile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, false));
		Projectile->SetActorRelativeLocation(FVector(ProjectileDistance, 0, 0));

		ProjectileArray.Add(Projectile);
	}

	for (int i = 0; i < ProjectileArray.Num(); ++i)
	{
		FVector RelativeLocation(ProjectileDistance, 0, 0);
		RelativeLocation = RelativeLocation.RotateAngleAxis((360 / ProjectileArray.Num()) * i, {0, 0, 1});
		ProjectileArray[i]->SetActorRelativeLocation(RelativeLocation);
	}
}

void ABible::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AddActorWorldRotation(FRotator(0, 1 * DeltaSeconds * RotateSpeed, 0));
}