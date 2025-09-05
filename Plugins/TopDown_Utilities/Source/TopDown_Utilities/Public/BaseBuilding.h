// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SelectInterface.h"
#include "FactionInterface.h"
#include "BaseBuilding.generated.h"

class UBoxComponent;
struct FInputActionValue;
class UEnhancedInputComponent;
class UInputAction;

UCLASS()
class TOPDOWN_UTILITIES_API ABaseBuilding : public AActor, public ISelectInterface,public IFactionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBuilding();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> IndicateStaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PlaceAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building", Meta = (AllowPrivateAccess = "true"))
	FTimerHandle TH_CheckValidity;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Faction)
	int32 FactionID = 0;

	int32 GetFactionID_Implementation() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Building)
	FName CanPlaceFlag = "CanPlaceBuilding";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Building)
	FVector BoxExtents = FVector(1100, 1100, 370);

	bool bCanPlace = false;

	void SetFactionID_Implementation(int32 val) override;

	UFUNCTION(BlueprintImplementableEvent,Category = Building)
	void TogglePlaceBuildingColor(bool bValid);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SelectActor_Implementation(const bool select);
	
	// Building placement mode
	UFUNCTION(BlueprintCallable)
	void EnablePlacingMode();

	// Check location validity for building 
	void CheckPlacementValidity();

	// Place the buiding 
	void PlaceBuilding(const FInputActionValue& value);

		//Cancel building placement
	void CancelBuildingPlacement(const FInputActionValue& Value);
};
