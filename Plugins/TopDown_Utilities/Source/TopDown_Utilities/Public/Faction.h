// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonEnum.h"
#include "Faction.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct  FFaction : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Faction)
	int32 FactionID;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Faction)
	EColor Color;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Faction)
	TSoftObjectPtr<UMaterialInstance> FactionPawnMaterial;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Faction)
	TSoftObjectPtr<UMaterialInstance> FactionHouseMaterial;
	
	FFaction() :
		FactionID(0), FactionPawnMaterial(nullptr), FactionHouseMaterial(nullptr),Color(EColor::Black){}

	FFaction(int32 id, TSoftObjectPtr<UMaterialInstance> PawnMaterial, TSoftObjectPtr<UMaterialInstance> houseMaterial, EColor Col):
		FactionID(id),FactionPawnMaterial(PawnMaterial), FactionHouseMaterial(houseMaterial), Color(Col) {}
};
