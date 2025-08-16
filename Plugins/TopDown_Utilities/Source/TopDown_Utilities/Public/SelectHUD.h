// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SelectHUD.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_UTILITIES_API ASelectHUD : public AHUD
{
	GENERATED_BODY()
	
private:
	FVector2D SelectBeginLoc;

	FVector2D SelectAreaSize;
	
	bool bDrawSelectArea;
	
	FLinearColor SelectAreaColor = FLinearColor(1.0f, 0.f, 0.f, 0.2f);

	TArray<AActor*> RectActors;

	bool bBeginSelectAction = false;

protected:
	virtual void DrawHUD() override;

	void SelectActorsInRect();

public:
	void SetShowDrawArea(const FVector2D BeginLoc, const FVector2D Size);

	void SetHideDrawArea();

	TArray<AActor*> GetSelctActors();
};
