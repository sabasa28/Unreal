// Copyright Epic Games, Inc. All Rights Reserved.


#include "ArcadeTopDownShooterGameModeBase.h"

#include "Interfaces/ScoreInterface.h"
#include "Kismet/GameplayStatics.h"

void AArcadeTopDownShooterGameModeBase::BeginPlay()
{
	CurrentGameProgressState = EGameProgressState::GameInit;
	
	Super::BeginPlay();	
}

void AArcadeTopDownShooterGameModeBase::StartGame()
{
	CurrentGameProgressState = EGameProgressState::GameInProgress;
	
	IScoreInterface* PConInterface = Cast<IScoreInterface>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PConInterface)
		PConInterface->ClearScore();
	
	RecieveStartGame();

}

void AArcadeTopDownShooterGameModeBase::EndGame(EGameResult result)
{
	CurrentGameProgressState = EGameProgressState::GameEnd;
	RecieveEndGame(result);

}

