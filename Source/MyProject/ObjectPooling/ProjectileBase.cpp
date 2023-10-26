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
	UE_LOG(LogTemp, Warning, TEXT("AProjectileBase::OnHitBoxBeginOverlap) this : %s, Overlapped Actor : %s"), *GetName(), *OtherActor->GetName());

	OtherActor->TakeDamage(Damage, FDamageEvent(UDamageType::StaticClass()), GetWorld()->GetFirstPlayerController(), this);

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


	AddActorWorldOffset( GetActorForwardVector() * Speed * DeltaTime, true);

	if (Distance != -1.0f)
	{
		CurrentDistance += Speed * DeltaTime;
		if (CurrentDistance >= Distance)
		{
			Deactivate();
		}
	}
}

void AProjectileBase::SetProjectileData(FProjectileData* NewProjectileData)
{
	if (NewProjectileData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AProjectileBase::SetProjectileData) ProjectileData is nullptr"));
		return;
	}
	StaticMeshComponent->SetStaticMesh(NewProjectileData->StaticMesh);
	StaticMeshComponent->SetMaterial(0, NewProjectileData->Material);
	StaticMeshComponent->SetRelativeScale3D(FVector(NewProjectileData->MeshScale));
	StaticMeshComponent->SetRelativeRotation(NewProjectileData->MeshRotation);
	Speed = NewProjectileData->Speed;
	Damage = NewProjectileData->Damage;
	PenetrateCount = NewProjectileData->PenetrateCount;
	Distance = NewProjectileData->Distance;
	CurrentDistance = 0.0f;
}

void AProjectileBase::Activate()
{
	Super::Activate();
	HitBox->SetCollisionProfileName(TEXT("Projectile"));
}

void AProjectileBase::Deactivate()
{
	Super::Deactivate();

	HitBox->SetCollisionProfileName(TEXT("NoCollision"));
}