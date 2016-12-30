// Copyright 2016, free to use

#include "BuildingEscape.h"
#include "OpenDoor.h"


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
	Owner = GetOwner();

}


/* void UOpenDoor::CloseDoor(float Time) {
	
	
	float AngleYaw = OpenAngle - Time / DoorClosedDelayTime * OpenAngle;

	if(Time > 0 && DoorClosedDelayTime != 0) {

		Owner->SetActorRotation(FRotator(0.0f, AngleYaw, 0.0f));

	}
	else Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));


}
*/


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );


	if(GetTotalMassOnPlate() >= TriggerMass) { 
		
		OnOpen.Broadcast();

	}
	else {
	
		OnClose.Broadcast();
	
	}

}


float UOpenDoor::GetTotalMassOnPlate() {

	float TotalMass = 0.0f;
	TArray<AActor*> OverlappingActors;

	if(!PressurePlate) {
	
		UE_LOG(LogTemp, Error, TEXT("Trigger Volume not chosen on %s"), *GetOwner()->GetName());
		return TotalMass;
	
	}

	else {
	
		PressurePlate->GetOverlappingActors(OverlappingActors);

		for(const auto& Actor : OverlappingActors) {

			UPrimitiveComponent* Component = Actor->FindComponentByClass<UPrimitiveComponent>();
			TotalMass += Component->GetMass();

		}

		return TotalMass;


	}
	
}

