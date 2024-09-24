// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"

// Sets default values
APaddle::APaddle()
{
	PrimaryActorTick.bCanEverTick = true;

	PaddleCollision = CreateDefaultSubobject<UBoxComponent>("PaddleCollision");
	PaddleMesh = CreateDefaultSubobject<UPaperSpriteComponent>("PaddleMesh");

	SetRootComponent(PaddleCollision);
	PaddleMesh->SetupAttachment(RootComponent);
	PaddleCollision->SetSimulatePhysics(true);
	PaddleCollision->SetEnableGravity(false);
	PaddleCollision->SetCollisionProfileName(TEXT("BlockAll"));
	PaddleCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PaddleCollision->SetBoxExtent(FVector(1, 1, 1));
	PaddleCollision->SetLinearDamping(10);

	PaddleCollision->GetBodyInstance()->bLockXRotation = true;
	PaddleCollision->GetBodyInstance()->bLockYRotation = true;
	PaddleCollision->GetBodyInstance()->bLockZRotation = true;
	PaddleCollision->GetBodyInstance()->bLockYTranslation = true;
	PaddleCollision->GetBodyInstance()->bLockXTranslation = true;
}

void APaddle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Controller)
	{
		FRotator rotation(0, 0, GetController()->GetControlRotation().Pitch);
		FVector direction = FVector::ZeroVector;

		if (movement)
		{
			direction = GetActorLocation() + FRotationMatrix(rotation).GetUnitAxis(EAxis::Z) * movement * (Speed*3) * DeltaTime;
			SetActorLocation(direction);
		}
	}
}

// Called to bind functionality to input
void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MovePaddle", this, &APaddle::moveRight);
	}
}

void APaddle::moveRight(float value)
{
	movement = value;
}

