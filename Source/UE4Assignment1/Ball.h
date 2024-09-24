// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"



UCLASS()
class UE4ASSIGNMENT1_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components")
		class USphereComponent* SphereCollision;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components")
		class UPaperSpriteComponent* BallMeshComponent;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components")
		class UProjectileMovementComponent* BallMovementComponent;

protected:
	ABall();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
