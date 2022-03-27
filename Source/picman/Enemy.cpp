// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyAIController.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 400.0f;
	ResettingTime = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = Speed;
	EnemyDisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemynDisplayMesh"));
	EnemyDisplayMesh->SetupAttachment(GetCapsuleComponent());
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	DefaultLocation = GetActorLocation();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::GetInjured()
{
	
	GetCharacterMovement()->MaxWalkSpeed = 0;
	SetActorLocation(DefaultLocation);
	GetWorldTimerManager().SetTimer(ResettingTimerHandle, this, &AEnemy::Resetting, ResettingTime, false);
}

void AEnemy::Resetting()
{
	GetWorldTimerManager().ClearTimer(ResettingTimerHandle);
	GetCharacterMovement()->MaxWalkSpeed = Speed;
	Cast<AMyAIController>(this->GetController())->GetNewDestination();
}

//void AEnemy::OnEnemyBeginOverlay(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{	
//}

