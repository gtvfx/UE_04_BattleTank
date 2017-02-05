// Copyright Gavyn Thompson 2017

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    auto ControlledTank = Cast<ATank>(GetPawn());

    if (ensure(PlayerTank))
    {
        // Move towards player
        MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in centimeters

        // Aim towards player
        ControlledTank->AimAt(PlayerTank->GetActorLocation());

        //ControlledTank->Fire(); 
    }
}