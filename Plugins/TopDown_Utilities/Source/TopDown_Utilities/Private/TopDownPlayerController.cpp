// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
ATopDownPlayerController::ATopDownPlayerController()
{
}

void ATopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!DefaultInputMappingContext)
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* System = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (System)
	{
		System->AddMappingContext(DefaultInputMappingContext, 0);
		UE_LOG(LogTemp,Display,TEXT("Mapping context added!"));
	}
}
