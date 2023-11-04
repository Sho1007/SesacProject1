// Fill out your copyright notice in the Description page of Project Settings.


#include "../Character/PlayerBase.h"

#include "EnemyBase.h"
#include "../Inventory/InventoryComponent.h"
#include "StatusComponent.h"
#include "Components/CapsuleComponent.h"
#include "../PlayerController/InGamePlayerController.h"
#include "MyProject/ObjectPooling/BossBoxBase.h"
#include "../Widget/GameOverWidget.h"

// Sets default values
APlayerBase::APlayerBase() : CurrentExp(0.0f), MaxExp(10.0f), CurrentLevel(1)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();

	//InventoryComponent->AddWeapon(TEXT("Dagger"));

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerBase::OnCapsuleComponentBeginOverlap);
}

// Called every frame
void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerBase::OnCapsuleComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
	ABossBoxBase* BossBox = Cast<ABossBoxBase>(OtherActor);
	if (Enemy || BossBox) return;
	//UE_LOG(LogTemp, Warning, TEXT("APlayerBase::OnCapsuleComponentBeginOverlap) OverlappedActor : %s"), *OtherActor->GetName());
	AddExp(10.0f);
	OtherActor->Destroy();
}

void APlayerBase::Die()
{
	check(GameOverWidgetClass);

	UGameOverWidget* GameOverWidget = CreateWidget<UGameOverWidget>(GetController<APlayerController>(), GameOverWidgetClass);
	GameOverWidget->AddToViewport();
}

void APlayerBase::AddExp(float NewExp)
{
	CurrentExp += NewExp;
	if (CurrentExp >= MaxExp)
	{
		CurrentExp -= MaxExp;

		CurrentLevel++;

		MaxExp = CurrentLevel * 10.0f;

		LevelUp();

		OnLevelUpdated.ExecuteIfBound(CurrentLevel);
	}

	OnExpUpdated.ExecuteIfBound(CurrentExp, MaxExp);
}

void APlayerBase::LevelUp()
{
	if (AInGamePlayerController* PC = GetController<AInGamePlayerController>())
	{
		PC->ShowLevelUpWidget();
	}
}