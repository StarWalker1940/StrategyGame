// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CommonEnum.h"
#include "BaseBuilding.h"
#include "PawnTypeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPawnTypeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOPDOWN_UTILITIES_API IPawnTypeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent,Category = "PawnTpye")
	EUnitType GetPawnType();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category = "BuildOption")
	TArray<TSubclassOf<ABaseBuilding>> GetBuildOption();
};
