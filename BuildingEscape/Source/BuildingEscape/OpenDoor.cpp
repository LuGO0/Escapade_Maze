// Copyright caSUALs 2018

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#define OUT


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
	/*ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();*/
	//pointer protection
	if (PressurePlate == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is missing pressure plate"), *GetOwner()->GetName());
	}
}





// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//ask every frame if the actor has overlapped the pressure plate or not by the ctor which could open the door
	if (TotalWeightOnThePressurePlate() > 150.0f)
	{
		//if yes then open the door
		OpenDoor();
		//DoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	else
	//close the door catch the player
	{
		CloseDoor();
	}

}


float UOpenDoor::TotalWeightOnThePressurePlate()
{
	float TotalMass=0;
	OUT TArray <AActor*>OverlappingActors;

	//TODO find the overlapping actors
	if (PressurePlate == nullptr)
	{
		return 0;
	}
	PressurePlate->GetOverlappingActors(

		//returns overlapping actors
		OUT OverlappingActors

		//second parameter is optional it filters out actors and return only if they are o a particular type
	);

		for (AActor* Actor : OverlappingActors)
		{
			//UE_LOG(LogTemp, Warning, TEXT("%s is overlapping the pressure plate"), *Actor->GetName())
				TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}

	//TODO iterate thru them adding their masses and return them as a whole

	return TotalMass;
}

void UOpenDoor::CloseDoor()
{
	////get owner of the object
	//AActor* Owner = GetOwner();

	////getting object name
	//FString ObjectName = Owner->GetName();

	////getting objects rotation
	//FString ObjectRotation = Owner->GetTransform().GetRotation().ToString();

	////create a rotator nd closing the door
	//FRotator NewRotation = FRotator(0.0f, 0.f, 0.0f);

	////setting object  rotation
	//Owner->SetActorRotation(NewRotation);


	/*printing out to log
	UE_LOG(LogTemp, Warning, TEXT("%s is rotated at %s"), *ObjectName, *ObjectRotation);
	*/

	CloseRequest.Broadcast();
}

void UOpenDoor::OpenDoor()
{
	////get owner of the object
	//AActor* Owner = GetOwner();

	////getting object name
	//FString ObjectName = Owner->GetName();

	////getting objects rotation
	//FString ObjectRotation = Owner->GetTransform().GetRotation().ToString();

	////create a rotator
	//FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f);

	////setting object  rotation
	//Owner->SetActorRotation(NewRotation);


	////printing out to log
	//UE_LOG(LogTemp, Warning, TEXT("%s is rotated at %s"), *ObjectName, *ObjectRotation);

	OpenRequest.Broadcast();
}
