// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "ArcadeTopDownShooter/Interfaces/ScoreInterface.h"

#include "ArcadeTDSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ARCADETOPDOWNSHOOTER_API AArcadeTDSPlayerController : public APlayerController, public IScoreInterface
{
	GENERATED_BODY()

protected:
	// Inputs

	/** Flag to prevent duplicate input bindings when using the same player controller for multiple maps*/
	bool bHasInitializedInputComponent = false;

	virtual void SetupInputComponent() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Called for shooting projectiles input */
	void Shoot();
	

	// Score

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int Score = 0;
	
	UFUNCTION(BlueprintCallable, Category = "Score")
	void ResetScore();

	/** Returns the score total*/
	UFUNCTION(BlueprintCallable, Category = "Score")
	int AddToScore(int value);

public:

	//Score Interface
	
	virtual void ClearScore() override;
	
	int AddValueToScore_Implementation(int value) override;
};
