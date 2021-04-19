// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcadeTDSPlayerController.h"
#include "ArcadeTopDownShooter/Interfaces/ShipInterface.h"

void AArcadeTDSPlayerController::ResetScore()
{
	Score = 0;
	UE_LOG(LogTemp, Warning, TEXT("Score has been reset to 0"));
}

int AArcadeTDSPlayerController::AddToScore(int value)
{
	Score = FMath::Max(Score + value, 0);
	UE_LOG(LogTemp, Warning, TEXT("Current Score: %d"), Score);
	
	return Score;
}

void AArcadeTDSPlayerController::ClearScore()
{
	ResetScore();
}

int AArcadeTDSPlayerController::AddValueToScore_Implementation(int value)
{
	return AddToScore(value);
}

void AArcadeTDSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!bHasInitializedInputComponent)
	{
		// Binding movement input
		InputComponent->BindAxis("MoveForward", this, &AArcadeTDSPlayerController::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &AArcadeTDSPlayerController::MoveRight);

		// Binding action input
		InputComponent->BindAction("Shoot", IE_Pressed, this, &AArcadeTDSPlayerController::Shoot);
		
		bHasInitializedInputComponent = true;
	}
}

void AArcadeTDSPlayerController::MoveForward(float Value)
{
	if(Value)
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// add movement in that direction
		GetPawn()->AddMovementInput(Direction, Value);
	}
}

void AArcadeTDSPlayerController::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement in that direction
		GetPawn()->AddMovementInput(Direction, Value);
	}
}

void AArcadeTDSPlayerController::Shoot()
{
	if (GetPawn()->GetClass()->ImplementsInterface(UShipInterface::StaticClass())) 
		IShipInterface::Execute_Shoot(GetPawn());
}
