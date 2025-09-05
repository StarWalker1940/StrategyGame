// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonEnum.h"
#include "PawnData.generated.h"

USTRUCT(BlueprintType)
struct FPawnData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Pawn")
	EUnitType PawnType;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Pawn")
	FString DisplayName;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Pawn")
	UTexture2D* Texture; 
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Pawn")
	int32 Health;

	FPawnData() : PawnType(EUnitType::Villager), DisplayName(""), Texture(nullptr), Health(100) {}

	FPawnData(EUnitType T, FString Name, UTexture2D* Tex, int32 Heal)
		: PawnType(T), DisplayName(Name), Texture(Tex), Health(Heal) {
	}
};