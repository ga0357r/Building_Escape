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
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
#pragma region Private Variables
	float initialYaw;
	float currentYaw;
	float doorLastOpened = 0.f;
	float targetYaw = 90.f;
	AActor* doorOpener;
#pragma endregion

#pragma region Private Serialized Variables
	UPROPERTY(EditAnywhere) float doorCloseDelay = 0.25f;
	UPROPERTY(EditAnywhere) float doorOpenSpeed = 0.65f;
	UPROPERTY(EditAnywhere) float doorCloseSpeed = 0.9f;
	UPROPERTY(EditAnywhere) ATriggerVolume* pressurePlate;
#pragma endregion

private:
	void Open(float deltaTime);
	void Close(float deltaTime);
};
