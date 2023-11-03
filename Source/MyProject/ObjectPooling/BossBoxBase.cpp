// Fill out your copyright notice in the Description page of Project Settings.


#include "../ObjectPooling/BossBoxBase.h"

#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/Character.h>

#include "../PlayerController/InGamePlayerController.h"

ABossBoxBase::ABossBoxBase()
{
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	check(Collider);
	SetRootComponent(Collider);
	Collider->SetCollisionProfileName(TEXT("LootItem"));
	Collider->SetSimulatePhysics(true);

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	check(BoxMesh);
	BoxMesh->SetupAttachment(RootComponent);
	BoxMesh->SetCollisionProfileName(TEXT("NoCollision"));
}

void ABossBoxBase::BeginPlay()
{
	Super::BeginPlay();

	if (Collider) Collider->OnComponentBeginOverlap.AddDynamic(this, &ABossBoxBase::OnColliderBeginOverlap);
}

void ABossBoxBase::OnColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		OpenBox(Character);
	}
}

void ABossBoxBase::OpenBox(ACharacter* TargetCharacter)
{
	if (AInGamePlayerController* PlayerController = TargetCharacter->GetController<AInGamePlayerController>())
	{
		float BoxChance = FMath::RandRange(0.0f, 100.0f);
		int ItemCount;

		if (BoxChance <= ChanceTo5)
		{
			ItemCount = 5;
			
		}
		else if (BoxChance <= ChanceTo5 + ChanceTo3)
		{
			ItemCount = 3;
		}
		else
		{
			ItemCount = 1;
		}

		//UE_LOG(LogTemp, Warning, TEXT("ABossBoxBase::OpenBox) Item Count : %d"), ItemCount);

		PlayerController->ShowBoxWidget(ItemCount);

		Destroy();
	}
}

void ABossBoxBase::Activate()
{
	Super::Activate();

	BoxMesh->SetVisibility(true);
}

void ABossBoxBase::Deactivate()
{
	Super::Deactivate();

	BoxMesh->SetVisibility(false);
}
