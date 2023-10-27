// Fill out your copyright notice in the Description page of Project Settings.


#include "../Character/EnemyBase.h"

#include <Components/CapsuleComponent.h>
#include <Components/BoxComponent.h>
#include <Components/SphereComponent.h>
#include <GameFramework/Character.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Engine/DamageEvents.h>

#include "../ObjectPooling/SpawnManager.h"

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
	SetActorRotation(FMath::Lerp(GetActorRotation(), MoveDirection.Rotation(), 0.5f));

	if (MoveDirection.Length() > RespawnDistance)
	{
		Respawn();
		return;
	}
	if (MoveDirection.Length() > 100.0f)
	{
		MoveDirection.Normalize();
		AddActorWorldOffset(MoveDirection * Speed * DeltaTime, true);
	}

	FVector ActorLocation = GetActorLocation();
	for (int i = 0; i < ObstacleComponentArray.Num(); ++i)
	{
		FVector ImpulseDirection = ObstacleComponentArray[i]->GetOwner()->GetActorLocation() - ActorLocation;
		ImpulseDirection.Normalize();
		ObstacleComponentArray[i]->AddImpulse(ImpulseDirection * ImpulsePower * Speed);
		UE_LOG(LogTemp, Error, TEXT("AEnemyBase::Tick) Impulse To %s"), *ObstacleComponentArray[i]->GetName());
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

	UE_LOG(LogTemp, Warning, TEXT("AEnemyBase::TakeDamage) Remain Health : %f"), CurrentHealth);

	if (CurrentHealth <= 0.0f) Die();

	return Result;
}

void AEnemyBase::Activate()
{
	Super::Activate();

	CurrentHealth = MaxHealth;
	ObstacleComponentArray.Empty();
	CapsuleComponent->SetCollisionProfileName(TEXT("Enemy"));
	CapsuleComponent->SetSimulatePhysics(true);
}

void AEnemyBase::Deactivate()
{
	Super::Deactivate();

	bIsAttackable = false;
	CurrentAttackCoolTime = AttackCoolTime;
	CapsuleComponent->SetSimulatePhysics(false);
	CapsuleComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void AEnemyBase::Die()
{
	if (LootItemClassArray.Num() > 0)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		for (int i = 0; i < LootItemClassArray.Num(); ++i)
		{
			if (LootItemClassArray[i]) AActor* LootItem = GetWorld()->SpawnActor<AActor>(LootItemClassArray[i], GetActorLocation(), GetActorRotation(), Params);
		}
	}

	Deactivate();
}

void AEnemyBase::Attack()
{
	TargetCharacter->TakeDamage(AttackDamage, FDamageEvent(UDamageType::StaticClass()), nullptr, this);
}

void AEnemyBase::Respawn()
{
	SpawnManager->RespawnEnemy(PoolingIndex);
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
		CurrentAttackCoolTime = AttackCoolTime;
	}
	else
	{
		ObstacleComponentArray.Remove(OtherComp);
	}
}

void AEnemyBase::Init(ASpawnManager* NewSpawnManager, int32 NewPoolingIndex)
{
	Super::Init(NewSpawnManager, NewPoolingIndex);

	TargetCharacter = SpawnManager->GetTargetCharacter();
}