// Fill out your copyright notice in the Description page of Project Settings.


#include "../Character/EnemyBase.h"

#include <Components/CapsuleComponent.h>
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
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	// Todo : ObjectPooling시에 TargetCharacter Set;
	
	TargetCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter();
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

	if (bIsAttacking) return;

	FVector MoveDirection = TargetCharacter->GetActorLocation() - GetActorLocation();

	if (MoveDirection.Length() <= AttackRange)
	{
		EnemyState = EEnemyState::ATTACK;
	}
	else
	{
		EnemyState = EEnemyState::CHASE;
	}


	switch (EnemyState)
	{
	case EEnemyState::CHASE:
		{
		SetActorRotation(FMath::Lerp(GetActorRotation(), MoveDirection.Rotation(), 0.5f));
		AvoidObstacle(MoveDirection);
		AddActorWorldOffset(MoveDirection * Speed * DeltaTime, true);
		}
		break;
	case EEnemyState::ATTACK:

		if (AttackMontage)
		{
			Attack();
		}

		break;
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
	CapsuleComponent->SetCollisionProfileName(TEXT("Enemy"));
}

void AEnemyBase::Deactivate()
{
	Super::Deactivate();

	StopAnimMontage();
	bIsAttacking = false;
	SetActorTickEnabled(bIsActivated);
	SetActorHiddenInGame(!bIsActivated);
	CapsuleComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void AEnemyBase::Die()
{
	Deactivate();
}

void AEnemyBase::Attack()
{
	bIsAttacking = true;
	PlayAnimMontage(AttackMontage);
}

void AEnemyBase::AvoidObstacle(FVector& MoveDirection)
{
	FHitResult OutHit;
	FVector Start = GetActorLocation() + (GetActorForwardVector() * 10.0f);
	FVector End = Start + (GetActorForwardVector() * 22.0f);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	// 시작 방향은 타겟
	MoveDirection = GetActorForwardVector();

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	// 보이는 것들을 회피
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Visibility));
	// 자기 자신과 타겟은 회피 안함
	TArray<AActor*> ActorsToIngore;
	ActorsToIngore.Add(this);
	ActorsToIngore.Add(TargetCharacter);

	// 만약 앞에 장애물이 있다면
	if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, 22.0f, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, ActorsToIngore, EDrawDebugTrace::ForOneFrame, OutHit, true))
	{
		// 오른쪽으로 한번 더 검사 후 있다면
		UE_LOG(LogTemp, Warning, TEXT("AEnemyBase::AvoidObstacle) HitActor : %s"), *OutHit.GetActor()->GetName());
		if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End + (GetActorRightVector() * 22.0f), 22.0f, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, ActorsToIngore, EDrawDebugTrace::ForOneFrame, OutHit, true))
		{
			// 방향을 왼쪽으로
			MoveDirection = -GetActorRightVector();
		}
		else
		{
			// 오른쪽에 장애물이 없다면 방향을 오른쪽으로
			MoveDirection = GetActorRightVector();
		}
	}
	// 후 벡터 정규화 
	MoveDirection.Normalize();
}

void AEnemyBase::CheckHit()
{
	FHitResult OutHit;
	FVector Start = GetActorLocation() + (GetActorForwardVector() * 30);
	FVector End = Start + (GetActorForwardVector() * AttackRange);

	FCollisionObjectQueryParams OQParams;
	// 플레이어를 체크 대상으로 등록
	OQParams.AddObjectTypesToQuery(ECC_GameTraceChannel2);

	//DrawDebugLine(GetWorld(), Start, End, FColor::Yellow, false, 0.5f);
	if (GetWorld()->LineTraceSingleByObjectType(OutHit, Start, End, OQParams))
	{
		UE_LOG(LogTemp, Warning, TEXT("AEnemyBase::CheckHit) Hit Actor : %s"), *OutHit.GetActor()->GetName());
		// 콜리전이 일어났다면 데미지 적용
		OutHit.GetActor()->TakeDamage(AttackDamage, FDamageEvent(UDamageType::StaticClass()), nullptr, this);
	}
}


void AEnemyBase::EndAttack()
{
	bIsAttacking = false;
}

// 최적화를 위해 Character가 아닌 Actor로 구현하여 PlayAnimMontage 함수를 Character 에서 가져옴
float AEnemyBase::PlayAnimMontage(UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
{
	UAnimInstance* AnimInstance = (SkeletalMeshComponent) ? SkeletalMeshComponent->GetAnimInstance() : nullptr;
	if (AnimMontage && AnimInstance)
	{
		float const Duration = AnimInstance->Montage_Play(AnimMontage, InPlayRate);

		if (Duration > 0.f)
		{
			// Start at a given Section.
			if (StartSectionName != NAME_None)
			{
				AnimInstance->Montage_JumpToSection(StartSectionName, AnimMontage);
			}

			return Duration;
		}
	}

	return 0.f;
}

void AEnemyBase::StopAnimMontage(UAnimMontage* AnimMontage)
{
	UAnimInstance* AnimInstance = (SkeletalMeshComponent) ? SkeletalMeshComponent->GetAnimInstance() : nullptr;
	UAnimMontage* MontageToStop = (AnimMontage) ? AnimMontage : (AnimInstance) ? AnimInstance->GetCurrentActiveMontage() : nullptr;
	bool bShouldStopMontage = AnimInstance && MontageToStop && !AnimInstance->Montage_GetIsStopped(MontageToStop);

	if (bShouldStopMontage)
	{
		AnimInstance->Montage_Stop(MontageToStop->BlendOut.GetBlendTime(), MontageToStop);
	}
}