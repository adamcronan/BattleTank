// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto MyControlledTank = GetPlayerControlledTank();
	if (MyControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank: %s is controlled by player"), *(MyControlledTank->GetName()))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO CONTROLLED TANK!"))
	}

	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"))
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetPlayerControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPlayerControlledTank()) { return; }

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation))  // Side effect: this will ray trace
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())
		// TODO Tell player controlled tank to aim at this point
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	HitLocation = FVector(1.0);
	return true;
}


