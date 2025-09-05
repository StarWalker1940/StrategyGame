// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FactionInterface.h"
#include "TopDownPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class ABasePawn;
class ASelectHUD;
/**
 * 
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectActorDelegate,const TArray<AActor*>&, SelectActors);

UCLASS()
class TOPDOWN_UTILITIES_API ATopDownPlayerController : public APlayerController,public IFactionInterface
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Faction)
	int32 FactionID = 0;

	int32 GetFactionID_Implementation() override;

	void SetFactionID_Implementation(int32 val) override;

	void CommandSelectActor(const FInputActionValue& Value);

	void SelectBegin(const FInputActionValue& Value);

	void SelectOnGoing(const FInputActionValue& Value);

	void SelectEnd(const FInputActionValue& Value);

	void SelectSingle();

	void SelectSingleImp();

	void SelectMutiActors(); 

	void DeSelectActors();

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

	TArray<ABasePawn*> SelectActors;

	UPROPERTY()
	TArray<AActor*> ActorsCanSelect;

	UPROPERTY(BlueprintAssignable,Category = "Delegate")
	FOnSelectActorDelegate OnActorsSelect;

};
