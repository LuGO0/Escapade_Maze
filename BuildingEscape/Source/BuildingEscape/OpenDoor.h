// Copyright caSUALs 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h" 
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"          //may be i think this has to be the last #include in the include list yes its true!!
 

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	//opens the door at this angle
	UPROPERTY(EditAnywhere)
		float OpenAngle=100.0f ;

	//trigger volume attribute added to opendoor component of actor door
	UPROPERTY(EditAnywhere)
	ATriggerVolume * PressurePlate=nullptr;

	//actor attribute to assign which actor could open the door by influencing the pressure plate
	/*UPROPERTY(EditAnywhere)*/
		/*AActor* ActorThatOpens;*/

		//real world tie at which door opens
		float DoorOpenTime;

		//door will be closed after this lag
		UPROPERTY(EditAnywhere)
			float DoorCloseLag = 0.45f;

		//
		float TotalWeightOnThePressurePlate();

		//dynamic multicast delegate BP friendly
		UPROPERTY(BlueprintAssignable)
		FOpenRequest OpenRequest;
	
		//
		UPROPERTY(BlueprintAssignable)
			FOpenRequest CloseRequest;
};

