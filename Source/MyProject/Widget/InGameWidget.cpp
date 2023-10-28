// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/InGameWidget.h"

#include "BoxWidget.h"

void UInGameWidget::ShowBoxWidget(const TArray<FName>& ItemNameArray)
{
	BoxWidget->ShowWidget(ItemNameArray);
}