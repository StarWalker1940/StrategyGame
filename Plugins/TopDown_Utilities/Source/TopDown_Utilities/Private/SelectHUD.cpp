// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectHUD.h"

void ASelectHUD::DrawHUD()
{
	Super::DrawHUD();

	if (bDrawSelectArea)
	{
		DrawRect(SelectAreaColor, SelectBeginLoc.X, SelectBeginLoc.Y, SelectAreaSize.X, SelectAreaSize.Y);
	}

	if (bBeginSelectAction)
	{
		SelectActorsInRect();
	}
}

void ASelectHUD::SelectActorsInRect()
{
	bBeginSelectAction = false;
	FVector2D FirstLoc = SelectBeginLoc;
	FVector2D SecondLoc = SelectBeginLoc + SelectAreaSize;

	RectActors.Empty();
	GetActorsInSelectionRectangle(FirstLoc, SecondLoc, RectActors, false);
}

void ASelectHUD::SetShowDrawArea(const FVector2D BeginLoc, const FVector2D Size)
{
	SelectBeginLoc = BeginLoc;
	SelectAreaSize = Size;
	bDrawSelectArea = true;
}

void ASelectHUD::SetHideDrawArea()
{
	bDrawSelectArea = false;
	bBeginSelectAction = true;
}

TArray<AActor*> ASelectHUD::GetSelctActors()
{
	return RectActors;
}
