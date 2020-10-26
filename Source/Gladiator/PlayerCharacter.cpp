// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
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

		FVector MoveDir = CamRot.RotateVector(FVector::RightVector);

		GetCharacterMovement()->AddInputVector(MoveDir * Val);


	}

}

void APlayerCharacter::MoveRight(float Val)
{
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