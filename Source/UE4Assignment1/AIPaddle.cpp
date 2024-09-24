// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPaddle.h"
#include "Ball.h"

void AAIPaddle::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
}

void AAIPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Ball)
	{
		FVector ballLocation = Ball->GetActorLocation();
		FVector targetLocation = GetActorLocation();
		targetLocation.Z = ballLocation.Z;
		SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), targetLocation, DeltaTime, DifficultyFactor));
	}
	else
	{
		SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), InitialLocation, DeltaTime, DifficultyFactor));
	}
}

void AAIPaddle::SetBall(ABall* ballToSet)
{
	Ball = ballToSet;
}


