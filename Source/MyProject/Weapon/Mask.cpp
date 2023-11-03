// Fill out your copyright notice in the Description page of Project Settings.


#include "../Weapon/Mask.h"

#include "MyProject/Character/StatusComponent.h"

void AMask::Attach(AActor* OwningCharacter)
{
	Super::Attach(OwningCharacter);

	StatusComponent->SetDuration(StatusComponent->GetDuration() + 0.1f);
}

void AMask::LevelUp()
{
	Super::LevelUp();

	switch (CurrentLevel)
	{
	case 2:
		StatusComponent->SetDuration(StatusComponent->GetDuration() + 0.1f);
		break;
	case 3:
		StatusComponent->SetDuration(StatusComponent->GetDuration() + 0.1f);
		break;
	case 4:
		StatusComponent->SetDuration(StatusComponent->GetDuration() + 0.1f);
		break;
	case 5:
		StatusComponent->SetDuration(StatusComponent->GetDuration() + 0.1f);
		break;
	}
}