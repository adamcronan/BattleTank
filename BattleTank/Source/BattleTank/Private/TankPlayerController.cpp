// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;

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
		GetPlayerControlledTank()->AimAt(HitLocation);
		// TODO Tell player controlled tank to aim at this point
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// line trace along that look direction, see what we hit
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	// "De-project" the screen position of the crosshair to a world direction
	FVector CameraWorldLocation; // Does not matter here
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();			// Where is the camera currently
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);	// Based on the way im looking, where is the end of this imaginary line
	if (GetWorld()->LineTraceSingleByChannel(								// Create line trace based on above vectors
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)									// Says if something is visible, I can hit it
		)																	// HitResult contains the thing that the line trace hit
	{
		HitLocation = HitResult.Location;									// Take the location of the thing that we hit
		return true;
	}
	HitLocation = FVector(0); 
	return false;   // Line trace didnt succeed
}


