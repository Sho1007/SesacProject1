// Fill out your copyright notice in the Description page of Project Settings.


#include "../Character/EnemyBase.h"

#include <Components/CapsuleComponent.h>
#include <Components/BoxComponent.h>
#include <GameFramework/Character.h>
#include <Engine/DamageEvents.h>
#include <Kismet/GameplayStatics.h>

#include "../ObjectPooling/SpawnManager.h"
#include "MyProject/ObjectPooling/ProjectileBase.h"

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
	if (MoveDirection.Length() > AttackRange)
	{
		//UE_LOG(LogTemp, Error, TEXT("AEnemyBase::Tick) Target Distance : %f"), MoveDirection.Length());
		MoveDirection.Normalize();
		AddActorWorldOffset(FVector(MoveDirection.X, MoveDirection.Y, 0) * Speed * DeltaTime, true);
	}

	FVector ActorLocation = GetActorLocation();
	for (int i = 0; i < ObstacleComponentArray.Num(); ++i)
	{
		FVector ImpulseDirection = ObstacleComponentArray[i]->GetOwner()->GetActorLocation() - ActorLocation;
		ImpulseDirection.Normalize();
		ObstacleComponentArray[i]->AddImpulse(ImpulseDirection * ImpulsePower * Speed);
		//UE_LOG(LogTemp, Error, TEXT("AEnemyBase::Tick) Impulse To %s"), *ObstacleComponentArray[i]->GetName());
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

	if (CurrentChangeMaterialTime > 0.0f)
	{
		CurrentChangeMaterialTime -= DeltaTime;
		if (CurrentChangeMaterialTime <= 0.0f)
		{
			SetDefaultMaterial();
		}
	}
}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	check(ImpactSound);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, GetActorLocation());

	float Result = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CurrentHealth -= DamageAmount;

	//UE_LOG(LogTemp, Warning, TEXT("AEnemyBase::TakeDamage) Damage : %f"), DamageAmount);

	if (CurrentHealth <= 0.0f) Die();

	// Change Material to Hitted
	if (HittedMaterial)
	{
		CurrentChangeMaterialTime = ChangeMaterialTime;
		for (int i = 0; i < DefaultMaterials.Num(); ++i)
		{
			SkeletalMeshComponent->SetMaterial(i, HittedMaterial);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AEnemyBase::TakeDamage) HittedMaterial is nullptr"));
	}

	if (AProjectileBase* Projectile = Cast<AProjectileBase>(DamageCauser))
	{
		AddActorWorldOffset(-Projectile->GetKnockback() * GetActorForwardVector() * BaseKnockback, true);
	}

	return Result;
}

void AEnemyBase::Activate()
{
	Super::Activate();

	SkeletalMeshComponent->SetVisibility(true);

	CurrentHealth = MaxHealth;
	ObstacleComponentArray.Empty();
	CapsuleComponent->SetCollisionProfileName(TEXT("Enemy"));
	CapsuleComponent->SetSimulatePhysics(true);
}

void AEnemyBase::Deactivate()
{
	Super::Deactivate();

	SkeletalMeshComponent->SetVisibility(false);

	SetDefaultMaterial();

	bIsAttackable = false;
	CurrentAttackCoolTime = AttackCoolTime;
	CapsuleComponent->SetSimulatePhysics(false);
	CapsuleComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void AEnemyBase::SetDefaultMaterial()
{
	CurrentChangeMaterialTime = 0.0f;
	for (int i = 0; i < DefaultMaterials.Num(); ++i)
	{
		SkeletalMeshComponent->SetMaterial(i, DefaultMaterials[i]);
	}
}

void AEnemyBase::Die()
{
	if (LootItemClassArray.Num() > 0)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		for (int i = 0; i < LootItemClassArray.Num(); ++i)
		{
			if (LootItemClassArray[i])
			{
				AActor* LootItem = GetWorld()->SpawnActor<AActor>(LootItemClassArray[i], GetActorLocation(), GetActorRotation(), Params);
			}
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

	DefaultMaterials = SkeletalMeshComponent->GetMaterials();
}