// Copyright Gabriel Alabi


#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Math/Color.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UE_LOG(LogTemp, Warning, TEXT("You can interact with objects"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//get player viewpoint
	FVector PlayerViewpointLocation = FVector::ZeroVector;
	FRotator PlayerViewpointRotation = FRotator::ZeroRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewpointLocation, 
		OUT PlayerViewpointRotation
	);

	//logging to viewpoint every click
	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"),
		*PlayerViewpointLocation.ToString(), *PlayerViewpointRotation.ToString()
	);

	//draw a line from player showing the reach
	FVector LineTraceEnd = PlayerViewpointLocation + FVector(0.f, 0.f, Reach);

	DrawDebugLine(
		GetWorld(), 
		PlayerViewpointLocation, LineTraceEnd,
		FColor::Red,
		false,
		0.f,
		0,
		5.f
	);

	//raycast out to a certain distance

	//see what it hits
}

