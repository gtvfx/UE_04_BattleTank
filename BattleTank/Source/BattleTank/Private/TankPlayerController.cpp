// Copyright Gavyn Thompson 2017

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "Tank.h" // needed for OnDeath event


void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// TODO: Subscribe local method
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }
    
    FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }

    FVector HitLocation; // OUT parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
    if (bGotHitLocation) // Has "side-effect": Ray Trace
    {
        AimingComponent->AimAt(HitLocation);
    }
}

// Get world location of linetrace through crosshair, return true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    // Find the crosshair position
    int32 ViewportSizeX, ViewportSizeY;

    GetViewportSize(ViewportSizeX, ViewportSizeY);

    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
    
    // 'De-project' the screen position of the crosshair to a world direction
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        // Line-trace along that LookDirection, and see what we hit (up to max range)
        
        return GetLookVectorHitLocation(LookDirection, HitLocation);
    }

    return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

    if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
    {
        HitLocation = HitResult.Location;
        return true;
    }

    HitLocation = FVector(0.0);
    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation; // Needed for the Deprojection method, but discarded after since we don't need it

    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}