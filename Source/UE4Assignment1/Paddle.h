// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Paddle.generated.h"

UCLASS()
class UE4ASSIGNMENT1_API APaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APaddle();

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components")
		class UBoxComponent* PaddleCollision;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components")
		class UPaperSpriteComponent* PaddleMesh;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Paddle Speed")
		float Speed = 30.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void moveRight(float value);

private:
	float movement;
};
