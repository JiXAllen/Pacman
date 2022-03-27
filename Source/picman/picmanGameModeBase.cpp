// Copyright Epic Games, Inc. All Rights Reserved.


#include "picmanGameModeBase.h"
#include "Picdot.h"
#include "Enemy.h"
#include "Engine/Public/EngineUtils.h"
#include "MyAIController.h"

ApicmanGameModeBase::ApicmanGameModeBase() 
{
	CurrentState = EGameState::EMenu;
}

void ApicmanGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<APicdot> PicdotIter(GetWorld()); PicdotIter; ++PicdotIter)
	{
		++PicdotNum;
	}

	for (TActorIterator<AEnemy> EnemyIter(GetWorld()); EnemyIter; ++EnemyIter)
	{
		Enemies.Add(Cast<AEnemy>(*EnemyIter));
	}
}

void ApicmanGameModeBase::StartGame()
{
	if (CurrentState == EGameState::EMenu)
	{
		SetCurrentState(EGameState::EPlay);
		for (auto Iter(Enemies.CreateIterator()); Iter; ++Iter)
		{
			Cast<AMyAIController>((*Iter)->GetController())->GetNewDestination();
		}
	}
	else if (CurrentState == EGameState::EGameOver)
	{
		GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));
	}
}

void ApicmanGameModeBase::PauseGame()
{
	if (CurrentState == EGameState::EPlay)
	{
		SetCurrentState(EGameState::EPause);
		GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("Pause"));
	}
	else if (CurrentState == EGameState::EPause)
	{
		SetCurrentState(EGameState::EPlay);
		GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("Pause"));
	}
}

void ApicmanGameModeBase::RestartGame()
{
	if (CurrentState == EGameState::EPlay || CurrentState == EGameState::EPause 
		|| CurrentState == EGameState::EWin || CurrentState == EGameState::EGameOver)
	{
		GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));
	}	
}

void ApicmanGameModeBase::EndGame()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("Exit"));
}




void ApicmanGameModeBase::SetPicdotNum(int Value)
{
	PicdotNum = Value;

	if (PicdotNum == 0)
	{
		SetCurrentState(EGameState::EWin);
	}
}

void ApicmanGameModeBase::SetCurrentState(EGameState Value)
{
	CurrentState = Value;

	switch (CurrentState)
	{
		case EGameState::EWin:
			for (auto Iter(Enemies.CreateIterator()); Iter; ++Iter)
			{
				(*Iter)->Destroy();
			}
			break;
	}

}