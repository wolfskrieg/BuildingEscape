// Copyright 2016, free to use

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	
	// Called when the game starts
	virtual void BeginPlay() override;

	void Grab();
	void Release();
	void FindPhysicsComponent();
	void SetupInputComponent();
	const FHitResult GetFirstPhysicsBodyInReach();
	
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr; 
	FVector PhysicsHandleLocation(FVector& );
	
};
