// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseShip.h"

#include "Engine/CollisionProfile.h"

// Sets default values
ABaseShip::ABaseShip()
{
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	
	ShipFloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovementComponent"));
	
	RootComponent = ShipMeshComponent;
	
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bIsInvincible = false;
}

// Called when the game starts or when spawned
void ABaseShip::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseShip::SetIsInvincible(bool Value)
{
	bIsInvincible = Value;
	OnInvincibilityValueChange(bIsInvincible);
}

// Called every frame
void ABaseShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseShip::SpawnProjectile()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;
	
	ABaseProjectile* SpawnedActor = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	MoveIgnoreActorAdd(SpawnedActor);
	
}

void ABaseShip::ActivateInvincibility(float Duration)
{
	SetIsInvincible(true);

	UE_LOG(LogTemp, Warning, TEXT("Ship is invincible"));
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, FString::Printf(TEXT("Invincible is %s"), (bIsInvincible ? TEXT("true") : TEXT("false"))));
	
	if (Duration > 0.0f)
	{
		GetWorldTimerManager().SetTimer(InvincibilityHandle, this,&ABaseShip::DeactivateInvincibility, Duration, false);
	}
}

 void ABaseShip::DeactivateInvincibility()
{
	 SetIsInvincible(false);
	
	UE_LOG(LogTemp, Warning, TEXT("Ship is not invincible"));
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, FString::Printf(TEXT("Invincible is %s"), (bIsInvincible ? TEXT("true") : TEXT("false"))));
}

void ABaseShip::Shoot_Implementation()
{
	SpawnProjectile();
}

int ABaseShip::AddValueToScore_Implementation(int value)
{
	if (GetController()->GetClass()->ImplementsInterface(UScoreInterface::StaticClass()))
		return IScoreInterface::Execute_AddValueToScore(GetController(), value);

	return -1;
}

