// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOPDOWN_UTILITIES_API APlayerPawn : public APawn
{
	GENERATED_BODY()

	//Capsule Component
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Collision,Meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* CapsuleComponent;

	//Spring Arm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, Meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, Meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
