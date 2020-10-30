// Fill out your copyright notice in the Description page of Project Settings.


#include "ArenaCharacter.h"

#include "PickableItemBase.h"
#include "PickableWeapon.h"

#include "Components/BoxComponent.h"

// Sets default values
AArenaCharacter::AArenaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AArenaCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArenaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	if (bIsAttacking) {

		if (WeaponCollider)
			WeaponCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	}

	else {

		if (WeaponCollider)
			WeaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		bCanDetectColliison = false;

	}

}

// Called to bind functionality to input
void AArenaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AArenaCharacter::PickShield(APickableItemBase* pickedShield)
{

	if (!pickedShield)
		return false;

	if (!Shield) {

		if (pickedShield->AttachItemTo(GetMesh(), TEXT("DualWeaponPoint")) == true) {

			Shield = pickedShield;
			return true;

		}


	}

	return false;


}

bool AArenaCharacter::PickWeapon(APickableWeapon* pickedWeapon)
{

	if (!pickedWeapon)
		return false;

	if (!Weapon) {

		if (pickedWeapon->AttachItemTo(GetMesh(), TEXT("WeaponPoint")) == true) {

			Weapon = pickedWeapon;
			
			WeaponCollider = pickedWeapon->GetDamageBox();

			if (WeaponCollider)
				WeaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			WeaponCollider->OnComponentBeginOverlap.AddDynamic(this, &AArenaCharacter::OnWeaponBeginOverlap);

			return true;

		}

	}

	return false;
}

void AArenaCharacter::Attack()
{

	if (Weapon) {

		bIsAttacking = true;
		bCanDetectColliison = true;


	}


}

void AArenaCharacter::OnWeaponBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweepFrom, const FHitResult& SweepResult)
{	

	if (!bCanDetectColliison)
		return;
	
	if (OtherActor->IsA(AArenaCharacter::StaticClass())) {

		bCanDetectColliison = false;
		
		UE_LOG(LogTemp, Warning, TEXT("Collided with AArenaCharacter"))
	
	}


}

