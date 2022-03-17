// Copyright Gabriel Alabi

#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/PlayerController.h"
#include "Math/Color.h"
#include "Grabber.h"

#define OUT

#pragma region Constructor Definition
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
#pragma endregion

#pragma region Begin Play Definition
// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandleComponent)
	{
		//physics handle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no UPhysicsHandleComponent attached"), *GetOwner()->GetName());
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		//Input Component is found
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Drop);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no Input Component attached"), *GetOwner()->GetName());
	}
}
#pragma endregion

#pragma region Tick Definition
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
		UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *ActorHit->GetName());
	}
	else
	{
		TraceColor = FColor::Red;
	}
}
#pragma endregion

#pragma region Private Methods
void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed"));	
}

void UGrabber::Drop()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Released"));
}
#pragma endregion

