// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "Enemy.h"
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"

void AMyAIController::OnPossess(APawn* PawnToPossess)
{
	Super::OnPossess(PawnToPossess);

	ControlledEnemy = Cast<AEnemy>(PawnToPossess);
}

void AMyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	GetNewDestination();
}

void AMyAIController::GetNewDestination()
{
	UNavigationSystemV1* NavMesh = UNavigationSystemV1::GetCurrent(this);
	if (NavMesh)
	{
		float SearchRadius = 2000.0f;
		FNavLocation RandomLocation;
		bool bNewDestinationFound = NavMesh->GetRandomReachablePointInRadius(ControlledEnemy->GetActorLocation(), SearchRadius, RandomLocation);
		if (bNewDestinationFound)
		{
			MoveToLocation(RandomLocation.Location, 50.0f);
		}
	}
}
