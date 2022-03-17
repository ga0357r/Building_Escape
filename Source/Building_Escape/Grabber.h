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

#pragma region Constructor
public:
	// Sets default values for this component's properties
	UGrabber();
#pragma endregion

#pragma region Begin Play
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
#pragma endregion

#pragma region Tick
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#pragma endregion

#pragma region Private Fields
private:
	//private fields
	UPROPERTY(EditAnywhere) float Reach = 100.f;
	FColor TraceColor = FColor::Red;
	UPhysicsHandleComponent* PhysicsHandleComponent = nullptr;
	UInputComponent* InputComponent = nullptr;
#pragma endregion

#pragma region Private Methods
private:
	void Grab();
	void Drop();
#pragma endregion

};
