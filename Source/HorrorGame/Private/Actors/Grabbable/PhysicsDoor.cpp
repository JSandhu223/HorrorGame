// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Grabbable/PhysicsDoor.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
APhysicsDoor::APhysicsDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	this->RootComponent = SceneRoot;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrame->SetupAttachment(SceneRoot);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(DoorFrame);
	Door->SetWorldLocation(FVector(0.0f, 45.0f, 0.0f));
	Door->SetSimulatePhysics(true);
	Door->SetMassOverrideInKg(NAME_None, 150.0f, true);
	Door->SetAngularDamping(4.0f); // determines how easily the door can be pushed open
	Door->BodyInstance.bLockXTranslation = true;
	Door->BodyInstance.bLockYTranslation = true;
	Door->BodyInstance.bLockZTranslation = true;
	Door->BodyInstance.bLockXRotation = true;
	Door->BodyInstance.bLockYRotation = true;

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("PhysicsConstraint"));
	PhysicsConstraint->SetupAttachment(SceneRoot);
	PhysicsConstraint->SetWorldLocation(FVector(0.0f, 45.0f, 0.0f));
	PhysicsConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Limited, 90.0f); // allows the door to swing +90 and -90 degrees maximum on only one axis
	PhysicsConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	PhysicsConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.0f);
	PhysicsConstraint->SetConstrainedComponents(DoorFrame, NAME_None, Door, NAME_None);
	PhysicsConstraint->SetDisableCollision(true); // prevents our two constrained components from colliding with each other
	/* ENABLE PROJECTION AND SET THE ANGULAR TOLERANCE TO 90 IN THE BLUEPRINT DERIVED CLASS. PROJECTION SETTINGS DON'T SEEM TO BE AVAILABLE THROUGH C++ FOR UNREAL 5.3.2. */
}

// Called when the game starts or when spawned
void APhysicsDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APhysicsDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APhysicsDoor::GrabObject()
{
	// Optional: Disable player movement (i.e. WASD movement) and camera movement when player interacts with the door

	UE_LOG(LogTemp, Warning, TEXT("Grabbed physics door!"));
}

void APhysicsDoor::ReleaseObject()
{
	UE_LOG(LogTemp, Warning, TEXT("Released object!"));
}
