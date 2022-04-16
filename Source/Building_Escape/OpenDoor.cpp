// Copyright Gabriel Alabi


#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#define OUT

#pragma region Constructor Definition
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
#pragma endregion

#pragma region Begin Play Definition
// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	initialYaw = GetOwner()->GetActorRotation().Yaw;
	currentYaw = initialYaw;
	targetYaw += currentYaw;
}
#pragma endregion

#pragma region Tick Definition
// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassOfActors() >= RequiredMass)
	{
		Open(DeltaTime);
		doorLastOpened = GetWorld()->GetTimeSeconds();
	}

	else
	{
		if ((GetWorld()->GetTimeSeconds() - doorLastOpened) >= DoorCloseDelay)
		{
			Close(DeltaTime);
		}
	}
}
#pragma endregion

#pragma region Private Method Definitions
void UOpenDoor::Open(float deltaTime)
{
	currentYaw = FMath::Lerp(currentYaw, targetYaw, DoorOpenSpeed * deltaTime);
	FRotator rotation = GetOwner()->GetActorRotation();
	rotation.Yaw = currentYaw;
	GetOwner()->SetActorRotation(rotation);
}

void UOpenDoor::Close(float deltaTime)
{
	currentYaw = FMath::Lerp(currentYaw, initialYaw, DoorCloseSpeed * deltaTime);
	FRotator rotation = GetOwner()->GetActorRotation();
	rotation.Yaw = currentYaw;
	GetOwner()->SetActorRotation(rotation);
}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no pressure plate set"), *GetOwner()->GetName());
		return TotalMass;
	}

	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for(AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}
#pragma endregion