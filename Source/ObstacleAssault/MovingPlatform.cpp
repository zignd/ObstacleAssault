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

	StartLocation = this->GetActorLocation();

	UE_LOG(LogTemp, Display, TEXT("Something is written here %f"), this->MoveDistance);
	UE_LOG(LogTemp, Warning, TEXT("Shit happened")); 
	UE_LOG(LogTemp, Error, TEXT("Damn error"));
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->MovePlatform(DeltaTime);

	this->RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if (ShouldPlatformReturn())
	{
		FVector MoveDirection = this->PlatformVelocity.GetSafeNormal();
		this->StartLocation = this->StartLocation + MoveDirection * this->MoveDistance;
		this->SetActorLocation(this->StartLocation);
		this->PlatformVelocity = -this->PlatformVelocity;
	}
	else
	{
		FVector CurrentLocation = this->GetActorLocation();
		CurrentLocation += PlatformVelocity * DeltaTime;
		this->SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	UE_LOG(LogTemp, Display, TEXT("Heya Rotating... %f"), DeltaTime);
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(this->StartLocation, this->GetActorLocation());
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return this->GetDistanceMoved() > this->MoveDistance;
}