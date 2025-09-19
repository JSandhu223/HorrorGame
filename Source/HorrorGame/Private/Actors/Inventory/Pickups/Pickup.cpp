// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Inventory/Pickups/Pickup.h"
#include "Components/SphereComponent.h"
#include "Game/Level1/L1Character.h"
#include "Components/InventoryComponent.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	this->RootComponent = SceneRoot;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneRoot);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	CollisionSphere->SetupAttachment(SceneRoot);
	CollisionSphere->SetSphereRadius(100.0f);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnSphereOverlap);
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::OnSphereOverlap(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AL1Character* PlayerRef = Cast<AL1Character>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s collided with %s"), *this->GetName(), *OtherActor->GetName());
		UInventoryComponent* PlayerInventoryComp = PlayerRef->GetInventoryComp();
		int32 OutRemainder = 0;
		bool bIsSuccess = PlayerInventoryComp->AddItem(this->Item, this->Amount, OutRemainder);
		if (bIsSuccess)
		{
			this->Destroy();
		}
	}
}