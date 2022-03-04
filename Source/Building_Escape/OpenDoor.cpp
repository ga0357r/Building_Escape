// Copyright Gabriel Alabi


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	initialYaw = GetOwner()->GetActorRotation().Yaw;
	currentYaw = initialYaw;
	targetYaw += currentYaw;

	if (!pressurePlate) UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component attached, but no pressure plate set"), *GetOwner()->GetName());
	
	if (!doorOpener)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component attached, but no door opener set"), *GetOwner()->GetName());
		doorOpener = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(LogTemp, Warning, TEXT("Door rotation is %s"), *GetOwner()->GetActorRotation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Target Yaw is %f"), targetYaw);

	if (pressurePlate && pressurePlate->IsOverlappingActor(doorOpener))
	{
		Open(DeltaTime);
		doorLastOpened = GetWorld()->GetTimeSeconds();
	}

	else
	{	
		if ((GetWorld()->GetTimeSeconds() - doorLastOpened) >= doorCloseDelay)
		{
			Close(DeltaTime);
		}
	}
}

void UOpenDoor::Open(float deltaTime)
{
	currentYaw = FMath::Lerp(currentYaw, targetYaw, doorOpenSpeed * deltaTime);
	FRotator rotation = GetOwner()->GetActorRotation();
	rotation.Yaw = currentYaw;
	GetOwner()->SetActorRotation(rotation);
}

void UOpenDoor::Close(float deltaTime)
{
	currentYaw = FMath::Lerp(currentYaw, initialYaw, doorCloseSpeed * deltaTime);
	FRotator rotation = GetOwner()->GetActorRotation();
	rotation.Yaw = currentYaw;
	GetOwner()->SetActorRotation(rotation);
}