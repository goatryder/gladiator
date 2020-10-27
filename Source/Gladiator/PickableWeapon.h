// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableItemBase.h"

#include "PickableWeapon.generated.h"

class UBoxComponent;
class USphereComponent;

UCLASS()
class GLADIATOR_API APickableWeapon : public APickableItemBase
{
	GENERATED_BODY()
	
public:

	APickableWeapon();

	virtual void BeginPlay() override;

	UBoxComponent* GetDamageBox() const;

protected:

	UPROPERTY(EditAnywhere)
		USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere)
		UBoxComponent* DamageBox;

};
