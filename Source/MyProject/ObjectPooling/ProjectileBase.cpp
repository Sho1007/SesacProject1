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
}

void AProjectileBase::OnHitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("AProjectileBase::OnHitBoxBeginOverlap) Overlapped Actor : %s"), *OtherActor->GetName());

	OtherActor->TakeDamage(Damage, FDamageEvent(UDamageType::StaticClass()), GetWorld()->GetFirstPlayerController(), this);

	if (--PenetrateCount <= 0) Destroy();
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
}