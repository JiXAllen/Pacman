// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class PICMAN_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* PicmanDisplayMesh;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void StartGame();
	void PauseGame();
	void RestartGame();
	void EndGame();

	void GetInjured();
	void Resetting();
	void GetWeak();
	

	UFUNCTION()
	void OnPicmanBeginOverlay(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Lifes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InvincibleTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ToughTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterialInstance* Tough;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterialInstance* Weak;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterialInstance* Invincible;

	FTimerHandle ResettingTimerHandle;

	bool isWeak;

private:
	
	FVector DefaultLocation;
	FVector Velocity;
	class ApicmanGameModeBase* GameModeRef;
	
};