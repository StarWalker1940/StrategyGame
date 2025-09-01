// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EResourceType :uint8
{
	Wood UMETA(DisplayName = "Wood"),
	Food UMETA(DisplayName = "Food"),
	Gold UMETA(DisplayName = "Gold"),
	Stone UMETA(DisplayName = "Stone"),
	Population UMETA(DisplayName = "Population")
}; 

UENUM(BlueprintType)
enum class EUnitType :uint8
{
	Villager UMETA(DisplayName = "Villager"),
	SwordMan UMETA(DisplayName = "SwordMan"),
	Knight UMETA(DisplayName = "Knight"),
	Archer UMETA(DisplayName = "Archer")
};

UENUM(BlueprintType)
enum class EColor :uint8
{
	Black UMETA(DisplayName = "Black"),
	Red UMETA(DisplayName = "Red"),
	Blue UMETA(DisplayName = "Blue"),
	Green UMETA(DisplayName = "Green"),
	White UMETA(DisplayName = "White"),
	Yellow UMETA(DisplayName = "Yellow")
};