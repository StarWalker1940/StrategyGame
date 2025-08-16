// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopDownPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class ABasePawn;
class ASelectHUD;
/**
 * 
 */
UCLASS()
class TOPDOWN_UTILITIES_API ATopDownPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATopDownPlayerController();
	
	//mapping context
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultInputMappingContext;

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent()	override;

	void Select(const FInputActionValue& Value);

	void CommandSelectActor(const FInputActionValue& Value);

	void SelectBegin(const FInputActionValue& Value);

	void SelectOnGoing(const FInputActionValue& Value);

	void SelectEnd(const FInputActionValue& Value);

	void SelectMutiActors();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SelectInputAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> CommandInputAction;

	UPROPERTY()
	TObjectPtr<AActor> SelectPawn;

	UPROPERTY()
	TObjectPtr< ASelectHUD> SelectHUD;

	UPROPERTY()
	FVector2D SelectBeginLoc;

	TArray<AActor*> SelectActors;
};
