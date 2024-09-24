// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PongGameState.generated.h"

/**
 * 
 */
UCLASS()
class UE4ASSIGNMENT1_API APongGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BLueprintReadOnly, Category = "Config")
		int32 PlayerScore = 0;
	UPROPERTY(VisibleAnywhere, BLueprintReadOnly, Category = "Config")
		int32 AIScore = 0;
	
};
