// Copyright Gavyn Thompson 2017

#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    auto TankName = GetName();
    UE_LOG(LogTemp, Warning, TEXT("***** %s: Tank C++ Construct *****"), *TankName);
}

void ATank::BeginPlay()
{
    Super::BeginPlay();

    auto TankName = GetName();
    UE_LOG(LogTemp, Warning, TEXT("***** %s: Tank C++ BeginPlay *****"), *TankName);
}

void ATank::AimAt(FVector HitLocation)
{
    if (!ensure(TankAimingComponent)) { return; }

    TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
    if (!ensure(Barrel)) { return; }

    bool isReloaded = (FPlatformTime::Seconds() - LastFireTime > ReloadTimeInSeconds);

    if (isReloaded)
    {

        // Spawn projectile at barrel location
        auto Projectile = GetWorld()->SpawnActor<AProjectile>
        (
            ProjectileBlueprint,
            Barrel->GetSocketLocation(FName("Projectile")),
            Barrel->GetSocketRotation(FName("Projectile"))
        );

        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
    }
}