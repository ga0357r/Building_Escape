// Copyright Gabriel Alabi

#include "Grabber.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Math/Color.h"

#define OUT

#pragma region Constructor Definition
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}
#pragma endregion

#pragma region Begin Play Definition
// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle();
	BindGrabInput();
}
#pragma endregion

#pragma region Tick Definition
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandleComponent) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("%s has no UPhysicsHandleComponent attached"), *GetOwner()->GetName());
		return; 
	}

	//if the physics handle is attached
	if (PhysicsHandleComponent->GrabbedComponent)
	{
		//move the object we are holding
		PhysicsHandleComponent->SetTargetLocation(CalculatePlayerReach());
	}
}
#pragma endregion

#pragma region Private Method Definitions
void UGrabber::Grab()
{
	FHitResult PhysicsBodyActor = ReturnPhysicsBodyActor();
	UPrimitiveComponent* ComponentToGrab = PhysicsBodyActor.GetComponent();
	AActor* ActorHit = PhysicsBodyActor.GetActor();


	if (ActorHit)
	{
		if (!PhysicsHandleComponent) 
		{ 
			UE_LOG(LogTemp, Error, TEXT("%s has no UPhysicsHandleComponent attached"), *GetOwner()->GetName());
			return; 
		}

		PhysicsHandleComponent->GrabComponentAtLocation(ComponentToGrab, NAME_None, CalculatePlayerReach());
		LockActorRotation(ActorHit);
	}
}

void UGrabber::Drop()
{
	if (!PhysicsHandleComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no UPhysicsHandleComponent attached"), *GetOwner()->GetName());
		return;
	}

	if (PhysicsHandleComponent->GrabbedComponent)
	{
		UnlockActorRotation(PhysicsHandleComponent->GrabbedComponent->GetOwner());
	}

	PhysicsHandleComponent->ReleaseComponent();
}

void UGrabber::FindPhysicsHandle()
{
	PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandleComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no UPhysicsHandleComponent attached"), *GetOwner()->GetName());
	}
}

void UGrabber::BindGrabInput()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Drop);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no Input Component attached"), *GetOwner()->GetName());
	}
}

FHitResult UGrabber::ReturnPhysicsBodyActor() const
{	
	//raycast out to a certain distance
	FHitResult OutHit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType
	(
		OUT OutHit,
		GetPlayerPosition(),
		CalculatePlayerReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	AActor* ActorHit = OutHit.GetActor();

	if (ActorHit)
	{
		//log out to test
		UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *ActorHit->GetName());
	}
	
	return OutHit;
}

FVector UGrabber::CalculatePlayerReach() const
{
	FVector PlayerLocation = FVector::ZeroVector;
	FRotator PlayerRotation = FRotator::ZeroRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);

	return PlayerLocation + (PlayerRotation.Vector() * Reach);
}

FVector UGrabber::GetPlayerPosition() const
{
	FVector PlayerLocation = FVector::ZeroVector;
	FRotator PlayerRotation = FRotator::ZeroRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);

	return PlayerLocation;
}

bool UGrabber::IsActorRotationLocked(const AActor* Actor)
{
	if (Actor->FindComponentByClass<UPrimitiveComponent>()->BodyInstance.bLockRotation == true) 
	{
		return true; 
	}

	else 
	{
		return false;
	}
}

void UGrabber::LockActorRotation(const AActor* Actor)
{
	Actor->FindComponentByClass<UPrimitiveComponent>()->BodyInstance.bLockXRotation = true;
	Actor->FindComponentByClass<UPrimitiveComponent>()->BodyInstance.bLockYRotation = true;
	Actor->FindComponentByClass<UPrimitiveComponent>()->BodyInstance.bLockZRotation = true;
}

void UGrabber::UnlockActorRotation(const AActor* Actor)
{
	Actor->FindComponentByClass<UPrimitiveComponent>()->BodyInstance.bLockXRotation = false;
	Actor->FindComponentByClass<UPrimitiveComponent>()->BodyInstance.bLockYRotation = false;
	Actor->FindComponentByClass<UPrimitiveComponent>()->BodyInstance.bLockZRotation = false;
}
#pragma endregion

