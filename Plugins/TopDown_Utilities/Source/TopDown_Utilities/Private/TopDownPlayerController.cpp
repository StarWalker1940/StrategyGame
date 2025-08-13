// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "BasePawn.h"

ATopDownPlayerController::ATopDownPlayerController()
{
	bShowMouseCursor = true;
}

void ATopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!DefaultInputMappingContext)
	{
		return;
	}

	//Add Mapping Context
	UEnhancedInputLocalPlayerSubsystem* System = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (System)
	{
		System->AddMappingContext(DefaultInputMappingContext, 0);
		UE_LOG(LogTemp,Display,TEXT("Mapping context added!"));
	}

	//Bind Select Action
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (EnhancedInputComponent != nullptr)
	{
		EnhancedInputComponent->BindAction(SelectInputAction, ETriggerEvent::Completed, this, &ATopDownPlayerController::Select);
	}
}

void ATopDownPlayerController::Select(const FInputActionValue& Value)
{
	FHitResult HitResult;

	GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);
	AActor* HitActor = HitResult.GetActor();

	if (HitActor != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("selcet Actor = %s"), *HitActor->GetName());
		if (SelectPawn != nullptr)
		{
			SelectPawn->SetIndicateShow(false);
		}

		 SelectPawn = Cast<ABasePawn>(HitActor);
		if (SelectPawn != nullptr)
		{
			SelectPawn->SetIndicateShow(true);
		}
	}
}
