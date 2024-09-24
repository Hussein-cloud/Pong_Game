// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

UCLASS()
class UE4ASSIGNMENT1_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* UpBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* BottomBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* Player01Box;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* Player02Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UCameraComponent* LevelCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UArrowComponent* SpawnPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UPaperSpriteComponent* BoardSprite;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		TSubclassOf<class ABall> BallTemplate;

	void SetCanSpawn(bool canSpawn);
	void SetAIPaddle(class AAIPaddle* newAI);
	void NullifyBallReference();
	void SpawnBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	ABoard();

	virtual void PostInitializeComponents() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private: 
	UPROPERTY(BluePrintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		class AAIPaddle* AI_Paddle;
	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		bool bCanSpawn = 1;
	UPROPERTY(BluePrintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		class APongGameState* PongGameState;
	UPROPERTY(BluePrintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		FTimerHandle SpawnTimer;
	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		float SpawnDelay = 3.f;

	UFUNCTION()
		void OnPlayer01BoxOverlapBegin(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnPlayer02BoxOverlapBegin(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
};
