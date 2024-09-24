// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Paddle.h"
#include "AIPaddle.generated.h"

/**
 * 
 */
UCLASS()
class UE4ASSIGNMENT1_API AAIPaddle : public APaddle
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Difficulty Factor")
		float DifficultyFactor = 300;

	virtual void Tick(float DeltaTime) override;
	void SetBall(class ABall* ballToSet);

protected:
	UPROPERTY(VisibleAnyWhere, Category = "Config")
		class ABall* Ball;

	FVector InitialLocation;

	virtual void BeginPlay() override;
};
