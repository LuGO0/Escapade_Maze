// Copyright caSUALs 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/Color.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetupInputComponent();


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Get the body which is being hit and is a physics body
	FHitResult GetFirstPhysicsBodyInReach();

	//get the end of TraceLIne
	FVector GetLineTraceEnd();

	//Get the start of ray cast line
	FVector GetLineTraceStart();

private:
	//reach of pawn
	float Reach = 100.0f;

	// i will find out why this dosent work
	FColor LineColor{ 255,0,0 };

	//actual function which take care of grabbing and is bound to grab action mapping
	void Grab();

	//drop function delegated to drop action
	void Drop();

	//template for finding components
	template<typename T>
	T* FindComponents();

	//found physics handle default pawn 
	UPhysicsHandleComponent* PhysicsHandle;
};
