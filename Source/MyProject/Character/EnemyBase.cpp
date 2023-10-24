// Fill out your copyright notice in the Description page of Project Settings.


#include "../Character/EnemyBase.h"

#include <Components/CapsuleComponent.h>
#include <Components/BoxComponent.h>
#include <Components/SphereComponent.h>
#include <GameFramework/Character.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Engine/DamageEvents.h>

#include "UObject/ObjectPtr.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetCollisionProfileName(TEXT("Enemy"));
	SetRootComponent(CapsuleComponent);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));

	MoveBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	MoveBoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	// Todo : ObjectPooling½Ã¿¡ TargetCharacter Set;
	
	TargetCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter();

	MoveBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnMoveBoxBeginOverlap);
	MoveBoxComponent->OnComponentEndOverlap.AddDynamic(this, &AEnemyBase::OnMoveBoxEndOverlap);
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetCharacter == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AEnemyBase::Tick) TargetCharacter is nullptr"));
		return;
	}

	MoveDirection = TargetCharacter->GetActorLocation() - GetActorLocation();

	MoveDirection.Normalize();
	SetActorRotation(FMath::Lerp(GetActorRotation(), MoveDirection.Rotation(), 0.5f));

	AddActorWorldOffset(MoveDirection * Speed * DeltaTime, true);

	FVector ActorLocation = GetActorLocation();
	for (int i = 0; i < ObstacleComponentArray.Num(); ++i)
	{
		FVector ImpulseDirection = ObstacleComponentArray[i]->GetOwner()->GetActorLocation() - ActorLocation;
		ImpulseDirection.Normalize();
		ObstacleComponentArray[i]->AddImpulse(ImpulseDirection * ImpulsePower * Speed);
	}
	if (bIsAttackable)
	{
		CurrentAttackCoolTime += DeltaTime;
		if (CurrentAttackCoolTime >= AttackCoolTime)
		{
			CurrentAttackCoolTime -= AttackCoolTime;
			Attack();
		}
	}
}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float Result = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHealth -= DamageAmount;

	if (CurrentHealth <= 0.0f) Die();

	return Result;
}

void AEnemyBase::Activate()
{
	Super::Activate();

	SetActorTickEnabled(bIsActivated);
	SetActorHiddenInGame(!bIsActivated);
	ObstacleComponentArray.Empty();
	CapsuleComponent->SetCollisionProfileName(TEXT("Enemy"));
	CapsuleComponent->SetSimulatePhysics(true);
}

void AEnemyBase::Deactivate()
{
	Super::Deactivate();

	bIsAttackable = false;
	CurrentAttackCoolTime = 0.0f;
	SetActorTickEnabled(bIsActivated);
	SetActorHiddenInGame(!bIsActivated);
	CapsuleComponent->SetSimulatePhysics(false);
	CapsuleComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void AEnemyBase::Die()
{
	Deactivate();
}

void AEnemyBase::Attack()
{
	TargetCharacter->TakeDamage(AttackDamage, FDamageEvent(UDamageType::StaticClass()), nullptr, this);
}

void AEnemyBase::OnMoveBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		bIsAttackable = true;
	}
	else
	{
		ObstacleComponentArray.Add(OtherComp);
	}
}

void AEnemyBase::OnMoveBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		bIsAttackable = false;
	}
	else
	{
		ObstacleComponentArray.Remove(OtherComp);
	}
}