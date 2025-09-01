// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SelectInterface.h"
#include "NavigableInterface.h"
#include "CommonEnum.h"
#include "PawnTypeInterface.h"
#include "FactionInterface.h"
#include "BasePawn.generated.h"


class UCapsuleComponent;
class UFloatingPawnMovement;

UCLASS()
class TOPDOWN_UTILITIES_API ABasePawn : public APawn, public ISelectInterface, public INavigableInterface, public IPawnTypeInterface, public IFactionInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess="true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletonMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> IndicateStaticMeshComponent;
public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Navigation
	FVector MoveTargetLocation = FVector::ZeroVector;
	bool bMoving = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Navigate)
	float AcceptanceDistance = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Navigate)
	float CharacterTurnSpeed = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = Pawn)
	EUnitType pawnType = EUnitType::Villager;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Faction)
	int32 FactionID = 0;

	EUnitType GetPawnType_Implementation() override;

	int32 GetFactionID_Implementation() override;

	void SetFactionID_Implementation(int32 val) override;


	void OrientPawnToMoveDirection();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void SetIndicateShow(const bool IsShow);
	
	void SelectActor_Implementation(const bool Select) override;

	void MoveToLocation_Implementation(const FVector TargetLocation) override;
};
