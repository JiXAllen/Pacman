// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "picmanGameModeBase.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EGameState : uint8
{
	EMenu,
	EPlay,
	EPause,
	EWin,
	EGameOver
};

UCLASS()
class PICMAN_API ApicmanGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	ApicmanGameModeBase();

protected:

	virtual void BeginPlay() override;

public:

	void StartGame();
	void PauseGame();
	void RestartGame();
	void EndGame();


	int GetPicdotNum() const;
	void SetPicdotNum(int Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int PicdotNum;

	EGameState GetCurrentState() const;
	void SetCurrentState(EGameState Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EGameState CurrentState;

private:

	TArray<class AEnemy*> Enemies;

};

FORCEINLINE int ApicmanGameModeBase::GetPicdotNum() const
{
	return PicdotNum;
}


FORCEINLINE EGameState ApicmanGameModeBase::GetCurrentState() const
{
	return CurrentState;
}

