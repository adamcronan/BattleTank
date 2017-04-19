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
	UE_LOG(LogTemp, Warning, TEXT("Ticking.."))
}

ATank* ATankPlayerController::GetPlayerControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


