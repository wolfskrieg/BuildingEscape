// Copyright 2016, free to use

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

/*	
	void OpenDoor();
	void CloseDoor(float);
*/

	float GetTotalMassOnPlate();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;

private:
	/*
	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.0f;
	*/

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;
	
	/*
	UPROPERTY(EditAnywhere)
	float DoorClosedDelayTime = 1.f;
	*/

	UPROPERTY(EditAnywhere)
	float TriggerMass = 5.f;

	// float LastDoorOpenTime = 0.f;

	AActor* Owner;
};
