// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArcadeTopDownShooterGameModeBase.generated.h"

/**
 * 
 */
UENUM()
enum class EGameProgressState : uint8
{
	None,
	GameInit,
	GameInProgress,
	GameEnd,
};

UENUM(BlueprintType)
enum class EGameResult : uint8
{
	None,
	Win,
	Lose
};

UCLASS()
class ARCADETOPDOWNSHOOTER_API AArcadeTopDownShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	/** Variables */
	
	UPROPERTY(BlueprintReadOnly, Category = "GameFlow")
	EGameProgressState CurrentGameProgressState;

	/** Functions */

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "GameFlow")
	void StartGame();

	UFUNCTION(BlueprintCallable, Category = "GameFlow")
	void EndGame(EGameResult Result);

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "GameFlow", meta=(DisplayName = "OnStartGame"))
	void RecieveStartGame();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameFlow", meta=(DisplayName = "OnEndGame"))
	void RecieveEndGame(EGameResult Result);
	
};