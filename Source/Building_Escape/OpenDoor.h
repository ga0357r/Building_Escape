// Copyright Gabriel Alabi

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
#pragma region Constructor
	// Sets default values for this component's properties
	UOpenDoor();
#pragma endregion

#pragma region Tick
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#pragma endregion

protected:
#pragma region Begin Play
	// Called when the game starts
	virtual void BeginPlay() override;
#pragma endregion

private:
#pragma region Private Variables
	float initialYaw = 0.f;
	float currentYaw = 0.f;
	float doorLastOpened = 0.f;
	float targetYaw = 90.f;
#pragma endregion

#pragma region Private Serialized Variables
	UPROPERTY(EditAnywhere) float DoorCloseDelay = 0.25f;
	UPROPERTY(EditAnywhere) float DoorOpenSpeed = 0.65f;
	UPROPERTY(EditAnywhere) float DoorCloseSpeed = 0.9f;
	UPROPERTY(EditAnywhere) ATriggerVolume* PressurePlate = nullptr;
	UPROPERTY(EditAnywhere) float RequiredMass = 50.f;
#pragma endregion

#pragma region Private Methods
	void Open(float deltaTime);
	void Close(float deltaTime);
	float TotalMassOfActors() const;
#pragma endregion
};
