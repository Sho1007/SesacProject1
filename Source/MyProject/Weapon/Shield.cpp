// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/Shield.h"

#include "MyProject/Character/StatusComponent.h"

void AShield::Attach(AActor* OwningCharacter)
{
	Super::Attach(OwningCharacter);

	StatusComponent->SetSpeed(StatusComponent->GetSpeed() + 0.1f);
}

void AShield::LevelUp()
{
	Super::LevelUp();

	switch(CurrentLevel)
	{
	case 2:
		StatusComponent->SetSpeed(StatusComponent->GetSpeed() + 0.1f);
		break;
	case 3:
		StatusComponent->SetSpeed(StatusComponent->GetSpeed() + 0.1f);
		break;
	case 4:
		StatusComponent->SetSpeed(StatusComponent->GetSpeed() + 0.1f);
		break;
	case 5:
		StatusComponent->SetSpeed(StatusComponent->GetSpeed() + 0.1f);
		break;
	}
}