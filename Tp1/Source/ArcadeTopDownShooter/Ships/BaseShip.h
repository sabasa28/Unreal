// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "ArcadeTopDownShooter/Projectiles/BaseProjectile.h"
#include "ArcadeTopDownShooter/Interfaces/ShipInterface.h"
#include "ArcadeTopDownShooter/Interfaces/ScoreInterface.h"

#include "BaseShip.generated.h"

UCLASS()
class ARCADETOPDOWNSHOOTER_API ABaseShip : public APawn, public IShipInterface, public IScoreInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseShip();
	

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ships, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ShipMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = Ships, meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement* ShipFloatingPawnMovement;

	UPROPERTY(VisibleAnywhere, Category = Ships, meta = (AllowPrivateAccess = "true"))
	bool bIsInvincible;

	FTimerHandle InvincibilityHandle;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	TSubclassOf<class ABaseProjectile> ProjectileClass;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetIsInvincible(bool Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Ship")
	void SpawnProjectile();

	//** If the Duration is 0 or < 0 then the invincibility is indefinite, you would need to call DeactivateInvecibility()*/
	UFUNCTION(BlueprintCallable, Category = "Ship")
	void ActivateInvincibility(float Duration);

	UFUNCTION(BlueprintCallable, Category = "Ship")
	void DeactivateInvincibility();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ship")
	void OnInvincibilityValueChange(bool newInvincibilityValue);
	
	// Interfaces

	// Ship
	void Shoot_Implementation() override;

	// Score
	int AddValueToScore_Implementation(int value) override;
};
