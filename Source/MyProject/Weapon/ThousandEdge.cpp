// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/ThousandEdge.h"

#include "../ObjectPooling/ProjectileBase.h"
#include "GameFramework/Character.h"
#include "MyProject/Inventory/InventoryComponent.h"

void AThousandEdge::BeginPlay()
{
	Super::BeginPlay();

	PrepareProjectile();
}

void AThousandEdge::ThrowDagger()
{
	for (int i = 0; i < PoolLimit; ++i)
	{
		if (ProjectilePool[i]->IsActive() == false)
		{
			ProjectilePool[i]->SetProjectileData(nullptr,
				ProjectileSpeed * StatusSpeed,
				WeaponDamage * StatusMight,
				WeaponPierce,
				WeaponArea * StatusArea,
				WeaponKnockback);
			ProjectilePool[i]->SetActorLocationAndRotation(GetActorLocation() + FVector(0, FMath::RandRange(-20.0f, 20.0f), 45), GetActorRotation());
			ProjectilePool[i]->Activate();
			break;
		}
	}

	if (--CurrentProjectileCount == 0) GetWorld()->GetTimerManager().ClearTimer(AttackHandle);
}

void AThousandEdge::Attach(AActor* OwningCharacter)
{
	Super::Attach(OwningCharacter);

	if (ACharacter* Character = Cast<ACharacter>(OwningCharacter))
	{
		this->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		this->SetActorRelativeLocation(FVector(0, 0, 90));
		this->SetActorRelativeRotation(FRotator(0, 90, 0));
	}

	if (UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(OwningCharacter->GetComponentByClass(UInventoryComponent::StaticClass())))
	{
		InventoryComponent->RemoveIngredient(WeaponName);
	}
}

void AThousandEdge::Attack()
{
	Super::Attack();

	//UE_LOG(LogTemp, Warning, TEXT("AThousandEdge::Attack"));

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (AttackHandle.IsValid()) TimerManager.ClearTimer(AttackHandle);

	CurrentProjectileCount = ProjectileCount + StatusAmount;

	TimerManager.SetTimer(AttackHandle, this, &AThousandEdge::ThrowDagger, ProjectileInterval, true);
}

void AThousandEdge::PrepareProjectile()
{
	check(ProjectileClass);
	UWorld* World = GetWorld();
	check(World);
	for (int i = 0; i < PoolLimit; ++i)
	{
		AProjectileBase* Projectile = World->SpawnActor<AProjectileBase>(ProjectileClass);
		Projectile->Deactivate();
		ProjectilePool.Add(Projectile);
	}
}