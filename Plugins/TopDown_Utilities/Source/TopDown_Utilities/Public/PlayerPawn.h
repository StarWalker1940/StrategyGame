// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;
class UInputAction;
struct FInputActionValue;


UCLASS()
class TOPDOWN_UTILITIES_API APlayerPawn : public APawn
{
	GENERATED_BODY()

	//Capsule Component
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Collision,Meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	//Spring Arm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr <UCameraComponent> FollowCamera;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr <UInputAction> MoveAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr <UInputAction> ZoomAction;

	UPROPERTY(EditAnywhere, Category = Input, Meta = (AllowPrivateAccess = "true"))
	float CameraZoomSpeed = 10.f;

	UPROPERTY(EditAnywhere, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	float MaxOrthoWidth = 3000.f;

	UPROPERTY(EditAnywhere, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	float MinOrthoWidth = 300.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr <UFloatingPawnMovement> FloatingPawnMovementComponent;
public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

	void Zoom(const FInputActionValue& Value);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
