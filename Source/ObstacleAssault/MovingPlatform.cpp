// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

  MovePlatform(DeltaTime);
  RotatePlatform(DeltaTime);

  
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
  if (ShouldPlatformReturn())
  {
    FVector MoveDirection = PlatformVelocity.GetSafeNormal();
    StartLocation += (MoveDirection * MoveDistance);
    SetActorLocation(StartLocation);
    PlatformVelocity = -PlatformVelocity;
  }
  else
  {
    FVector CurrentLocation = GetActorLocation();
    CurrentLocation += PlatformVelocity * DeltaTime;
    SetActorLocation(CurrentLocation);
  }

  if (ShouldChangeDirection())
  {
    FVector MoveDirection = PlatformVelocity.GetSafeNormal();
    StartLocation += (MoveDirection * MoveDistance);
    SetActorLocation(StartLocation);
    PlatformVelocity = PlatformVelocity.RotateAngleAxis(90, MoveDirection.ZAxisVector);
  }
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
  AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
  return GetDistanceMoved() > MoveDistance;
}

bool AMovingPlatform::ShouldChangeDirection() const
{
  return ChangesDirection && ShouldPlatformReturn();
}

float AMovingPlatform::GetDistanceMoved() const
{
  return FVector::Distance(StartLocation, GetActorLocation());
}