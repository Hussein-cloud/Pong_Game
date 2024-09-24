// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "AIPaddle.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "PaperSpriteComponent.h"
#include "Ball.h"
#include "PongGameState.h"
#include "EngineUtils.h"
#include "Camera/CameraComponent.h"

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UpBox = CreateDefaultSubobject<UBoxComponent>("UpBox");
	BottomBox = CreateDefaultSubobject<UBoxComponent>("BottomBox");
	Player01Box = CreateDefaultSubobject<UBoxComponent>("Player01Box");
	Player02Box = CreateDefaultSubobject<UBoxComponent>("Player02Box");
	LevelCamera = CreateDefaultSubobject<UCameraComponent>("LevelCamera");
	SpawnPoint = CreateDefaultSubobject<UArrowComponent>("SpawnPoint");
	BoardSprite = CreateDefaultSubobject<UPaperSpriteComponent>("BoardSprite");

	SetRootComponent(BoardSprite);
	
	UpBox->SetupAttachment(RootComponent);
	BottomBox->SetupAttachment(RootComponent);
	Player01Box->SetupAttachment(RootComponent);
	Player02Box->SetupAttachment(RootComponent);
	LevelCamera->SetupAttachment(RootComponent);
	SpawnPoint->SetupAttachment(RootComponent);

	UpBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	UpBox->SetCollisionProfileName("BlockAll");
	UpBox->SetNotifyRigidBodyCollision(true);

	BottomBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BottomBox->SetCollisionProfileName("BlockAll");
	BottomBox->SetNotifyRigidBodyCollision(true);

	Player01Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Player01Box->SetCollisionProfileName("OverlapAll");
	Player01Box->SetNotifyRigidBodyCollision(true);

	Player02Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Player02Box->SetCollisionProfileName("OverlapAll");
	Player02Box->SetNotifyRigidBodyCollision(true);

	BoardSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoardSprite->SetCollisionProfileName("NoCollision");
	BoardSprite->SetNotifyRigidBodyCollision(false);
}

void ABoard::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Player01Box->OnComponentBeginOverlap.AddDynamic(this, &ABoard::OnPlayer01BoxOverlapBegin);
	Player02Box->OnComponentBeginOverlap.AddDynamic(this, &ABoard::OnPlayer02BoxOverlapBegin);

}

void ABoard::SetCanSpawn(bool canSpawn)
{
	bCanSpawn = canSpawn;
}

void ABoard::SetAIPaddle(AAIPaddle* newAI)
{
	AI_Paddle = newAI;
}

void ABoard::NullifyBallReference()
{
	AI_Paddle->SetBall(NULL);
}

void ABoard::SpawnBall()
{
	if (BallTemplate)
	{
		UWorld* const world = GetWorld();
		if (world) {
			FActorSpawnParameters SpawnParam;
			SpawnParam.Owner = this;
			SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			FTransform SpawnTransform = SpawnPoint->GetComponentTransform();
			ABall* SpawnedBall = world->SpawnActor<ABall>(BallTemplate, SpawnTransform, SpawnParam);
			if (SpawnedBall) {
				if (AI_Paddle)
					AI_Paddle->SetBall(SpawnedBall);
				bCanSpawn = false;
			}
		}
	}
}

void ABoard::BeginPlay()
{
	Super::BeginPlay();
	
	if (APongGameState* GS = Cast<APongGameState>(GetWorld()->GetGameState()))
	{
		PongGameState = GS;
	}

	TArray<AAIPaddle*> AIPaddles;
	for (TActorIterator<AAIPaddle> Item(GetWorld()); Item; ++Item)
		if (*Item)
			AIPaddles.Add(*Item);

	if (AIPaddles.IsValidIndex(0))
		AI_Paddle = AIPaddles[0];


	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if(PC)
	{
		PC->SetViewTargetWithBlend(this, 2.0, EViewTargetBlendFunction::VTBlend_Cubic);
	}



}

void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanSpawn)
	{
		SpawnBall();
	}


}

void ABoard::OnPlayer01BoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABall* Ball = Cast<ABall>(OtherActor))
	{
		Ball->Destroy();
	}
	PongGameState->AIScore++;
	int temp = PongGameState->AIScore;
	GEngine->AddOnScreenDebugMessage(5, 15.0f, FColor::Yellow, FString::Printf(TEXT("AI Score: %d"), temp));
}

void ABoard::OnPlayer02BoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABall* Ball = Cast<ABall>(OtherActor))
	{
		Ball->Destroy();
	}
	PongGameState->PlayerScore++;
	int temp = PongGameState->PlayerScore;
	GEngine->AddOnScreenDebugMessage(5, 15.0f, FColor::Yellow, FString::Printf(TEXT("Player Score: %d"), temp));
}

