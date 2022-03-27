// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Picdot.generated.h"

UCLASS(Blueprintable)
class PICMAN_API APicdot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APicdot();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* PicdotDisplayMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* PicdotCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSuperPicdot = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
