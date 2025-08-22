// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonEnum.h"
#include "ResourceData.generated.h"

USTRUCT(BlueprintType)
struct FResourceData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Resource")
	EResourceType E_ResourceType;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Resource")
	FString DisplayName;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Resource")
	UTexture2D* Texture;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Resource")
	int32 ItemNum;

	FResourceData() : E_ResourceType(EResourceType::Wood), DisplayName(""), Texture(nullptr), ItemNum(0) {}

	FResourceData(EResourceType Type, FString Name, UTexture2D* Tex, int32 Num)
		: E_ResourceType(Type), DisplayName(Name), Texture(Tex), ItemNum(Num) {}
};