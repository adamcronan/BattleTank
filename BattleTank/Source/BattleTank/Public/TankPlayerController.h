// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	ATank* GetPlayerControlledTank() const;

	// Start the tank moving the barrel so that a shot would hit where crosshair
	// intersects the world
	void AimTowardsCrosshair();
	
	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector&) const;
	
	
};
