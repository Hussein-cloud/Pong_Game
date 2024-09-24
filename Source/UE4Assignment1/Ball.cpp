// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "PaperSpriteComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Board.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	BallMeshComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Ball Mesh");
	BallMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("BallProjectileMovement");

	SetRootComponent(SphereCollision);

	BallMeshComponent->SetupAttachment(RootComponent);
	SphereCollision->SetSphereRadius(21.4f);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereCollision->SetCollisionProfileName(TEXT("BlockAll"));
	SphereCollision->GetBodyInstance()->bLockYTranslation = true;

	BallMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BallMovementComponent->ProjectileGravityScale = 0.f;
	BallMovementComponent->InitialSpeed = 1000.f;
	BallMovementComponent->MaxSpeed = 10000.f;
	BallMovementComponent->bShouldBounce = true;
	BallMovementComponent->Bounciness = 1.1f;
	BallMovementComponent->Friction = 0.f;
	InitialLifeSpan = 25.f;
}

void ABall::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);


	if (ABoard* Board = Cast<ABoard>(GetOwner()))
	{
		Board->NullifyBallReference();

		Board->SetCanSpawn(true);
	}
}
