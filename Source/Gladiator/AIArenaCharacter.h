// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArenaCharacter.h"
#include "AIArenaCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API AAIArenaCharacter : public AArenaCharacter
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APickableItemBase> ShieldClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APickableWeapon> WeaponClass;

	void CreateAndAttachWeapons();


};
