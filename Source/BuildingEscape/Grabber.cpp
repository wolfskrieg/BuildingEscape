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

	// Look for attached physics handle
	FindPhysicsComponent();
	SetupInputComponent();
	
}

void UGrabber::FindPhysicsComponent() {

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	
	if(!PhysicsHandle) {
	
		UE_LOG(LogTemp, Error, TEXT("Physics handle not found on %s"), *GetOwner()->GetName());
	}

}

void UGrabber::SetupInputComponent() {

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputComponent) {

			InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);

	} else { 
		
		// some code night get here in meantime
	
	}
}


void UGrabber::Grab() {

	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	AActor* ActorHit = HitResult.GetActor();

	if(!PhysicsHandle) { return; }
	if(ActorHit) PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, ActorHit->GetActorLocation(), ActorHit->GetActorRotation());
	
}


void UGrabber::Release() {

	if(!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
	UE_LOG(LogTemp, Warning, TEXT("Grab released"))

}


void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// if there is no physics handle
	if(!PhysicsHandle) { return; }
	// if the physics handle is attached
	if(PhysicsHandle->GrabbedComponent) {
	
		// move the object that we are holding
		FVector HandleResetLocation(0.f, 0.f, 0.f);
		PhysicsHandle->SetTargetLocationAndRotation(PhysicsHandleLocation(HandleResetLocation), PhysicsHandle->GrabbedComponent->GetOwner()->GetActorRotation());
	
	}
}

FVector UGrabber::PhysicsHandleLocation(FVector& out_location) {

	FRotator out_rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(out_location, out_rotation);

	float Reach = 150.f;
	FVector LineTraceEnd = out_location + out_rotation.Vector() * Reach;
	return LineTraceEnd;

}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach() {

	FHitResult Hit;
	FVector out_location, line_location;
	line_location = PhysicsHandleLocation(out_location);

	FCollisionQueryParams CollisionParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(

		Hit,
		out_location,
		line_location,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		CollisionParams

	);

	return Hit;

}