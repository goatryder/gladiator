// Fill out your copyright notice in the Description page of Project Settings.


#include "AIArenaCharacter.h"

#include "PickableItemBase.h"
#include "PickableWeapon.h"

#include "AIController.h"
#include "BrainComponent.h"

void AAIArenaCharacter::BeginPlay()
{

	Super::BeginPlay();
	
	CreateAndAttachWeapons();

}

void AAIArenaCharacter::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

}

void AAIArenaCharacter::CreateAndAttachWeapons()
{

	FVector Position = GetActorLocation();
	FRotator Rotation = GetActorRotation();

	if (ShieldClass)
		PickShield(Cast<APickableItemBase>(GetWorld()->SpawnActor(ShieldClass, &Position, &Rotation)));

	if (WeaponClass)
		PickWeapon(Cast<APickableWeapon>(GetWorld()->SpawnActor(WeaponClass, &Position, &Rotation)));

}

void AAIArenaCharacter::Attack()
{

	Super::Attack();



}

bool AAIArenaCharacter::ApplyDamage()
{

	bool IsDead = Super::ApplyDamage();

	if (IsDead) {

		AAIController* MyAI = Cast<AAIController>(GetController());
		//MyAI->BrainComponent->StopLogic("");
		MyAI->UnPossess();

	}


	return IsDead;

}
