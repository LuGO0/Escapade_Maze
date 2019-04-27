// Copyright caSUALs 2018

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Math/Color.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
    PhysicsHandle=FindComponents<UPhysicsHandleComponent>();
    SetupInputComponent();
}


///template for finding various components by class types in default pawn
template<typename T>
T* UGrabber::FindComponents()
{
	T* Component = GetOwner()->FindComponentByClass<T>();

	if (Component)
	{
		UE_LOG(LogTemp, Warning, TEXT("component found for %s"), *GetOwner()->GetName());
		return Component;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("not component found for %s"), *GetOwner()->GetName());
		return nullptr;
	}

	
}

void UGrabber::SetupInputComponent()
{
	///checking for input component in the default pawn class
	UInputComponent* InputComponent = FindComponents<UInputComponent>();

	//setting up the found input component
	if (InputComponent )
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component found for %s"), *GetOwner()->GetName());

		//input binding Grab action mapping
		InputComponent->BindAction(

			//exacltly the same as the editor
			"Grab",

			//if those keys are pressed
			IE_Pressed,

			//look into this component
			this,

			//for a function wid this signature
			&UGrabber::Grab
		);

		//release action on the same input component
		InputComponent->BindAction("Drop", IE_Released, this, &UGrabber::Drop);
	}
}


///custom grab function
void UGrabber::Grab()
{
	//TODO code for grabbing
	UE_LOG(LogTemp, Warning, TEXT("grab pressed"));

	//LINE TRACE try and reach any obj with phy handle

     FHitResult HitObject=GetFirstPhysicsBodyInReach();

	//which component of the hit object do yo wanna grab
	 UPrimitiveComponent* ComponentToGrab = HitObject.GetComponent();

	//if actor is hit
	AActor* ActorHit = HitObject.GetActor();
	
	///if we hit somethin with a physics handle then lift that object
	if (ActorHit)
	{
		PhysicsHandle->GrabComponent(

			//returns the static mesh of the object to hold
			ComponentToGrab,

			//no bones needed
			NAME_None,

			//get the current location of the object you re lifting
			ComponentToGrab->GetOwner()->GetActorLocation(),

			//enable rotation of the object
			true
		);
	}
}

///drop it
void UGrabber::Drop()
{
	PhysicsHandle->ReleaseComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		
		if (PhysicsHandle->GrabbedComponent)
		{
			PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
		}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{

	//draw debug line for physical representation of our supermans rays
	DrawDebugLine(

		GetWorld(),
		//world you are in

		GetLineTraceStart(),
		//startin point of your line

		GetLineTraceEnd(),
		//end point of your line

		LineColor,
		/*FColor(255,0,0),*/
		//color of the line

		false,
		//do you want your debug line to be persistent or not

		0.0f,
		//if yes lifetime of persistency

		0.0f,
		//depth priority

		5.0f
		//thickness of your line

	);


	///emit supermans rays out of his eyes
	FHitResult Hit;
	bool bIsThatHitting = GetWorld()->LineTraceSingleByObjectType(

		//info about the object being hit @OUT param
	    Hit,

		//start location
		GetLineTraceStart(),

		//end location
		GetLineTraceEnd(),

		//the type of object i want to query with the ray cast
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),

		//passing params to the unreal physics collision function
		FCollisionQueryParams(
			//i dont know about this parameter now
			FName(TEXT("")),

			//i didnt want complex trace
			false,

			// i dont want the trace line to collide with the pawn itself so i ignored myself
			GetOwner()
		)
	);
	return Hit;
}

FVector UGrabber::GetLineTraceEnd()
{

	//temp function params
	FVector GetPlayerViewPointLocation;
	FRotator GetPlayerViewPointRotation;

	//get the player viewpoint every tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(GetPlayerViewPointLocation, GetPlayerViewPointRotation);

	//log the current viepoint of the player
	UE_LOG(LogTemp, Warning, TEXT("Location:%s\nRotation:%s "), *GetPlayerViewPointLocation.ToString(), *GetPlayerViewPointRotation.ToString());

	//get the end position of the line trace
	FVector LineTraceEnd = GetPlayerViewPointLocation + (GetPlayerViewPointRotation.Vector())*Reach;

	return LineTraceEnd;
}


FVector UGrabber::GetLineTraceStart()
{

	//out_parameters of getplayerviewpoint function
	FVector GetPlayerViewPointLocation;
	FRotator GetPlayerViewPointRotation;

	//get the player viewpoint every tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(GetPlayerViewPointLocation, GetPlayerViewPointRotation);

	//log the current viepoint of the player
	UE_LOG(LogTemp, Warning, TEXT("Location:%s\nRotation:%s "), *GetPlayerViewPointLocation.ToString(), *GetPlayerViewPointRotation.ToString());

	//get the end position of the line trace
	FVector LineTraceStart = GetPlayerViewPointLocation;

	return LineTraceStart;
}
