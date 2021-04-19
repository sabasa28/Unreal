// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ScoreInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UScoreInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARCADETOPDOWNSHOOTER_API IScoreInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual void ClearScore();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Score")
	int AddValueToScore(int value);
};
