// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "PickableItemBase.h"
#include "PickableWeapon.h"


void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);


}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("CameraPitch", this, &APlayerCharacter::CameraPitch);
	PlayerInputComponent->BindAxis("CameraYaw", this, &APlayerCharacter::CameraYaw);
	
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::Attack);
}

void APlayerCharacter::MoveForward(float Val)
{

	if (!bIsAlive)
		return;

	if (!bIsAttacking) {

		FRotator CamRot = GetControlRotation();
		CamRot.Pitch = 0.f;

		FVector MoveDir = CamRot.RotateVector(FVector::ForwardVector);

		GetCharacterMovement()->AddInputVector(MoveDir * Val);


	}

}

void APlayerCharacter::MoveRight(float Val)
{

	if (!bIsAlive)
		return;

	if (!bIsAttacking) {

		FRotator CamRot = GetControlRotation();
		CamRot.Pitch = 0.f;

		FVector MoveDir = CamRot.RotateVector(FVector::RightVector);

		GetCharacterMovement()->AddInputVector(MoveDir * Val);


	}


}

void APlayerCharacter::CameraPitch(float Val)
{

	float Input = Val * 100.f * GetWorld()->GetDeltaSeconds();

	AddControllerPitchInput(Input);

}

void APlayerCharacter::CameraYaw(float Val)
{

	float Input = Val * 100.f * GetWorld()->GetDeltaSeconds();

	AddControllerYawInput(Input);

}

void APlayerCharacter::Attack()
{


}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlapComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool BFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->ActorHasTag("Shield")) {

		// UE_LOG(LogTemp, Warning, TEXT("Collided With SHIELD"));

		APickableItemBase* PickedShield = Cast<APickableItemBase>(OtherActor);
		PickShield(PickedShield);

	}

	else if (OtherActor->ActorHasTag("Hammer")) {

		// UE_LOG(LogTemp, Warning, TEXT("Collided With HAMMER"));

		APickableWeapon* PickedWeapon = Cast<APickableWeapon>(OtherActor);
		PickWeapon(PickedWeapon);

	}


}
