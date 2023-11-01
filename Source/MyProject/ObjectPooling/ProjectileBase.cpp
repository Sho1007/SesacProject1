// Fill out your copyright notice in the Description page of Project Settings.


#include "../ObjectPooling/ProjectileBase.h"

#include <Components/SphereComponent.h>
#include <Engine/DamageEvents.h>

AProjectileBase::AProjectileBase()
{
	HitBox = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(HitBox);
	HitBox->SetCollisionProfileName(TEXT("Projectile"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void AProjectileBase::OnHitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("AProjectileBase::OnHitBoxBeginOverlap) this : %s, Overlapped Actor : %s"), *GetName(), *OtherActor->GetName());

	Attack(OtherActor);

	if (PenetrateCount != -1 && --PenetrateCount <= 0) Deactivate();
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	HitBox->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnHitBoxBeginOverlap);

}

void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);

	if (Distance != -1.0f)
	{
		CurrentDistance += Speed * DeltaTime;
		if (CurrentDistance >= Distance)
		{
			Deactivate();
		}
	}
}

void AProjectileBase::SetProjectileData(FProjectileData* NewProjectileData, float NewSpeed, float NewDamage, float NewPierce, float NewArea, float NewKnockback)
{
	if (NewProjectileData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AProjectileBase::SetProjectileData) ProjectileData is nullptr"));
	}
	else
	{
		StaticMeshComponent->SetStaticMesh(NewProjectileData->StaticMesh);
		StaticMeshComponent->SetMaterial(0, NewProjectileData->Material);
		StaticMeshComponent->SetRelativeScale3D(FVector(NewProjectileData->MeshScale));
		StaticMeshComponent->SetRelativeRotation(NewProjectileData->MeshRotation);
	}
	Speed = NewSpeed * BaseSpeed;
	Damage = NewDamage;
	PenetrateCount = NewPierce;
	Distance = NewArea * BaseDistance;
	Knockback = NewKnockback;
}

void AProjectileBase::Attack(AActor* TargetActor)
{
	TargetActor->TakeDamage(Damage, FDamageEvent(UDamageType::StaticClass()), GetWorld()->GetFirstPlayerController(), this);
}

void AProjectileBase::Activate()
{
	Super::Activate();
	HitBox->SetCollisionProfileName(TEXT("Projectile"));

	CurrentDistance = 0.0f;
}

void AProjectileBase::Deactivate()
{
	Super::Deactivate();

	HitBox->SetCollisionProfileName(TEXT("NoCollision"));
}

float AProjectileBase::GetSpeed() const
{
	return Speed;
}

float AProjectileBase::GetKnockback() const
{
	return Knockback;
}

void AProjectileBase::Move(float DeltaTime)
{
	AddActorWorldOffset(GetActorForwardVector() * Speed * DeltaTime);
}
