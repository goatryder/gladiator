// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArenaCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API APlayerCharacter : public AArenaCharacter
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	void MoveForward(float Val);
	void MoveRight(float Val);

	void CameraPitch(float Val);
	void CameraYaw(float Val);
	
	virtual void Attack() override;

public:

	UFUNCTION()
		virtual void OnBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool BFromSweep,
			const FHitResult& SweepResult);

};
