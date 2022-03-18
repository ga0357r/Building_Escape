// Copyright Gabriel Alabi

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
#pragma region Constructor
	// Sets default values for this component's properties
	UGrabber();
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
#pragma region Private Fields
	UPhysicsHandleComponent* PhysicsHandleComponent = nullptr;
	UInputComponent* InputComponent = nullptr;
#pragma endregion

#pragma region Private Serialized Fields
	UPROPERTY(EditAnywhere) float Reach = 100.f;
#pragma endregion

#pragma region Private Methods
	void Grab();
	void Drop();
	void FindPhysicsHandle();
	void BindGrabInput();
	FHitResult ReturnPhysicsBodyActor() const;
	FVector CalculateRaycastReach();
	FPlayerViewPoint GetPlayerViewPoint();
#pragma endregion
};
