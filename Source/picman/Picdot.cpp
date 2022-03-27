// Fill out your copyright notice in the Description page of Project Settings.


#include "Picdot.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
APicdot::APicdot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PicdotDisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PicdotDisplayMesh"));
	PicdotCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PicdotCollision"));

	PicdotDisplayMesh->SetupAttachment(PicdotCollision);
}

// Called when the game starts or when spawned
void APicdot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APicdot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

