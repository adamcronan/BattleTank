// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto MyControlledTank = GetControlledTank();
	if (MyControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank: %s is controlled"), *(MyControlledTank->GetName()))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO CONTROLLED TANK!"))
	}

	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"))
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


