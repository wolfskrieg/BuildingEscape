// Copyright 2016, free to use

#include "BuildingEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"))

	// Look for attached physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if(PhysicsHandle) {
	
		
	} else {
	
		UE_LOG(LogTemp, Error, TEXT("Object %s: Physics handle not found!"), *GetOwner()->GetName())
	}

	if(InputComponent) {

		UE_LOG(LogTemp, Warning, TEXT("Object %s: Input component found!"), *GetOwner()->GetName())
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		UE_LOG(LogTemp, Error, TEXT("Object %s: Input component not found!"), *GetOwner()->GetName())

	} else {

		UE_LOG(LogTemp, Error, TEXT("Object %s: Input component not found!"), *GetOwner()->GetName())
	}
	
}

void UGrabber::Grab() {

	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"))

}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
	FVector out_location;
	FRotator out_rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(out_location, out_rotation);

	//UE_LOG(LogTemp, Warning, TEXT("Location: %s , Rotation: %s"), *out_location.ToString(), *out_rotation.ToString());

	float Reach = 100.f;
	FVector LineTraceEnd = out_location + out_rotation.Vector() * Reach;

	DrawDebugLine(
		GetWorld(),
		out_location,
		LineTraceEnd,
		FColor::Red,
		false,
		0.f,
		0.f,
		2.f

	);
	FHitResult Hit;
	FCollisionQueryParams CollisionParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
	
		Hit,
		out_location,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		CollisionParams
	
	);

	AActor* ActorHit = Hit.GetActor();
	if(ActorHit) {
	
		//UE_LOG(LogTemp, Warning, TEXT("%s got hit!"), *(ActorHit->GetName()))
	}
	
}

