// Copyright Gabriel Alabi

#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
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

	//draw a line from player showing the reach
	FVector LineTraceEnd = PlayerViewpointLocation + (PlayerViewpointRotation.Vector() * Reach);

	DrawDebugLine(
		GetWorld(), 
		PlayerViewpointLocation, LineTraceEnd,
		TraceColor,
		false,
		0.f,
		0,
		5.f
	);

	//raycast out to a certain distance
	FHitResult OutHit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT OutHit,
		PlayerViewpointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	
	AActor* ActorHit = OutHit.GetActor();

	if (ActorHit)
	{
		TraceColor = FColor::Green;

		//log out to test
		UE_LOG(LogTemp, Error, TEXT("Actor: %s"), *ActorHit->GetName());
	}
	else
	{
		TraceColor = FColor::Red;
	}
}

