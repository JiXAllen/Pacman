// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Picdot.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "picmanGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Velocity = FVector(0, 0, 0);

	Lifes = 2;
	isWeak = true;
	Speed = 400.0f;
	InvincibleTime = 1.0f;
	ToughTime = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = Speed;

	PicmanDisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PicmanDisplayMesh"));
	PicmanDisplayMesh->SetupAttachment(GetCapsuleComponent());
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	DefaultLocation = GetActorLocation();

	GameModeRef = Cast<ApicmanGameModeBase>(UGameplayStatics::GetGameMode(this));

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnPicmanBeginOverlay);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("GameStart", IE_Pressed, this, &AMyCharacter::StartGame);
	PlayerInputComponent->BindAction("GamePause", IE_Pressed, this, &AMyCharacter::PauseGame);
	PlayerInputComponent->BindAction("Restart", IE_Pressed, this, &AMyCharacter::RestartGame);
	PlayerInputComponent->BindAction("GameEnd", IE_Pressed, this, &AMyCharacter::EndGame);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
}

void AMyCharacter::MoveForward(float Value)
{
	if (GameModeRef->GetCurrentState() == EGameState::EPlay)
	{
		Velocity.X = 0;
		Velocity.Y = Value;

		AddMovementInput(Velocity);
		if (Value > 0)
		{
			SetActorRotation(FRotator(0, 90, 0));
		}
		else if (Value < 0)
		{
			SetActorRotation(FRotator(0, -90, 0));
		}

	}

}

void AMyCharacter::MoveRight(float Value)
{
	if (GameModeRef->GetCurrentState() == EGameState::EPlay)
	{
		Velocity.X = Value;
		Velocity.Y = 0;
		AddMovementInput(Velocity);
		if (Value > 0)
		{
			SetActorRotation(FRotator(0, 0, 0));
		}
		else if (Value < 0)
		{
			SetActorRotation(FRotator(0, -180, 0));
		}
	}

}

void AMyCharacter::StartGame()
{
	GameModeRef->StartGame();
}

void AMyCharacter::PauseGame()
{
	GameModeRef->PauseGame();
}

void AMyCharacter::RestartGame()
{
	GameModeRef->RestartGame();
}

void AMyCharacter::EndGame()
{
	GameModeRef->EndGame();
}

void AMyCharacter::GetInjured()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Invincible"));

	Lifes--;
	if (Lifes == 0)
	{
		GameModeRef->SetCurrentState(EGameState::EGameOver);
	}
	else
	{
		SetActorLocation(DefaultLocation);
		PicmanDisplayMesh->SetMaterial(0, Invincible);
		GetWorldTimerManager().SetTimer(ResettingTimerHandle, this, &AMyCharacter::Resetting, InvincibleTime, false);
	}
}

void AMyCharacter::Resetting()
{
	GetWorldTimerManager().ClearTimer(ResettingTimerHandle);
	PicmanDisplayMesh->SetMaterial(0, Weak);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
}

void AMyCharacter::GetWeak()
{
	GetWorldTimerManager().ClearTimer(ResettingTimerHandle);
	isWeak = true;
	PicmanDisplayMesh->SetMaterial(0, Weak);
}

void AMyCharacter::OnPicmanBeginOverlay(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APicdot::StaticClass())) 
	{
		APicdot* CurrentPicdot = Cast<APicdot>(OtherActor);
		if (CurrentPicdot->bIsSuperPicdot)
		{
			isWeak = false;
			PicmanDisplayMesh->SetMaterial(0, Tough);
			GetWorldTimerManager().SetTimer(ResettingTimerHandle, this, &AMyCharacter::GetWeak, ToughTime, false);
		}
		OtherActor->Destroy();
		GameModeRef->PicdotNum--;	
		if (GameModeRef->PicdotNum == 0)
		{
			GameModeRef->SetCurrentState(EGameState::EWin);
		}
	}
	if (OtherActor->IsA(AEnemy::StaticClass()))
	{
		if (isWeak)
		{
			GetInjured();
		}
		else
		{
			Cast<AEnemy>(OtherActor)->GetInjured();
		}
	}
} 

