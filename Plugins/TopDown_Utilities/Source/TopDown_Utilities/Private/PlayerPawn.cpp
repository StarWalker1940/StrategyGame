// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Capsule
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;

	//Create SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	//Create Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

	//Create FloatingpawnMovement
	FloatingPawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	//Attach Components
	SpringArm->SetupAttachment(RootComponent);
	FollowCamera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
} 

void APlayerPawn::Move(const FInputActionValue& Value)
{
	const FVector2D MovementInput = Value.Get<FVector2D>();

	if (Controller)
	{
		const FRotator PlayerRotation = GetControlRotation();
		const FRotator YawRotator = FRotator(0, PlayerRotation.Yaw, 0);

		const FVector ForwordUnitVector = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
		const FVector RightUnitVector = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwordUnitVector, MovementInput.Y);
		AddMovementInput(RightUnitVector,MovementInput.X);
	}
}

void APlayerPawn::Zoom(const FInputActionValue& Value)
{
	const float ValueAlpha = Value.Get<float>();

	if (Controller != nullptr)
	{
		float DesireOrthorWidth = FollowCamera->OrthoWidth + ValueAlpha * CameraZoomSpeed;
		DesireOrthorWidth = FMath::Clamp(DesireOrthorWidth,MinOrthoWidth,MaxOrthoWidth);
		FollowCamera->OrthoWidth = DesireOrthorWidth;
	}
}


// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EdgeScollWithMouse();
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerPawn::Move);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &APlayerPawn::Zoom);
	}
}

void APlayerPawn::EdgeScollWithMouse()
{
	APlayerController* PC = Cast<APlayerController>(Controller);
	if (PC == nullptr)
		return;

	double MouseX = 0;
	double MouseY = 0;
	PC->GetMousePosition(MouseX, MouseY);

	if (GEngine && GEngine->GameViewport)
	{
		FVector2D ScreenSize;
		GEngine->GameViewport->GetViewportSize(ScreenSize);

		float EdgeThreshold = 100.f;
		FVector2D MoveValue = FVector2D::ZeroVector;

		if (MouseX < EdgeThreshold)
		{
			UE_LOG(LogTemp, Display, TEXT("向左移动"));
			MoveValue.X = -1.0f;
		}

		if (MouseX > (ScreenSize.X - EdgeThreshold))
		{
			UE_LOG(LogTemp, Display, TEXT("向右移动"));
			MoveValue.X = 1.0f;
		}

		if (MouseY < EdgeThreshold)
		{
			UE_LOG(LogTemp, Display, TEXT("向上移动"));
			MoveValue.Y = 1.0f;
		}

		if (MouseY > (ScreenSize.Y - EdgeThreshold))
		{
			UE_LOG(LogTemp, Display, TEXT("向下移动"));
			MoveValue.Y = -1.0f;
		}

		if (MoveValue.IsZero())
		{
			return;
		}
		Move(FInputActionValue(MoveValue));
	}
}

