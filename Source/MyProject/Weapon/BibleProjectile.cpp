// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/BibleProjectile.h"

void ABibleProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ActiveTime += DeltaSeconds;
}

void ABibleProjectile::Activate()
{
	Super::Activate();

	ActiveTime = 0.0f;
	CollisionMap.Empty();
}

void ABibleProjectile::Attack(AActor* TargetActor)
{
	if (CollisionMap.Contains(TargetActor->GetName()))
	{
		if (CollisionMap[TargetActor->GetName()] <= ActiveTime - MultiAttackAvoidTime)
		{
			CollisionMap[TargetActor->GetName()] = ActiveTime;
		}
		else
		{
			return;
		}
	}
	else
	{
		CollisionMap.Add(TargetActor->GetName(), ActiveTime);
	}

	Super::Attack(TargetActor);
}
