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
	

	if(PhysicsHandle) {


	} else {

		UE_LOG(LogTemp, Error, TEXT("Object %s: Physics handle not found!"), *GetOwner()->GetName())
	}

	

}

void UGrabber::SetupInputComponent() {

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputComponent) {

		UE_LOG(LogTemp, Warning, TEXT("Object %s: Input component found!"), *GetOwner()->GetName())
			InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);

	} else {

		UE_LOG(LogTemp, Error, TEXT("Object %s: Input component not found!"), *GetOwner()->GetName())
	}
}



void UGrabber::Grab() {

	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();

	AActor* ActorHit = HitResult.GetActor();

	if(ActorHit) PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ActorHit->GetActorLocation(), true);
	
}



void UGrabber::Release() {

	PhysicsHandle->ReleaseComponent();
	UE_LOG(LogTemp, Warning, TEXT("Grab released"))

}




void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// if the physics handle is attached
	if(PhysicsHandle->GrabbedComponent) {
	
		// move the object that we are holding
		PhysicsHandle->SetTargetLocation(HandleLocation());
	
	}
}

FVector UGrabber::HandleLocation() {

	FVector out_location;
	FRotator out_rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(out_location, out_rotation);



	float Reach = 150.f;
	FVector LineTraceEnd = out_location + out_rotation.Vector() * Reach;
	return LineTraceEnd;
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach() {

	FVector out_location;
	FRotator out_rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(out_location, out_rotation);
	


	float Reach = 200.f;
	FVector LineTraceEnd = out_location + out_rotation.Vector() * Reach;

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

	if(ActorHit) UE_LOG(LogTemp, Warning, TEXT("Actor hit"));
	return Hit;

}