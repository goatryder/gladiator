// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "PickableItemBase.h"
#include "PickableWeapon.h"

#include "Kismet/GameplayStatics.h"

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

	Super::Attack();


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

void APlayerCharacter::OnWeaponBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweepFrom, const FHitResult& SweepResult)
{

	if (!bCanDetectColliison)
		return;

	if (OtherActor == this)
		return;

	AArenaCharacter* OponentArenaChar = Cast<AArenaCharacter>(OtherActor);

	// if (OtherActor->IsA(AArenaCharacter::StaticClass())) {
	if (OponentArenaChar) {

		bCanDetectColliison = false;

		// UE_LOG(LogTemp, Warning, TEXT("Collided with AArenaCharacter"));

		bool OponentIsDead = OponentArenaChar->ApplyDamage();

		if (OponentIsDead) {
			
			FTimerHandle UnusedHandle;

			GetWorldTimerManager().SetTimer(
				UnusedHandle, this, &APlayerCharacter::RestartGame, 3.f, false);

		}

	}

}

bool APlayerCharacter::ApplyDamage()
{

	// UE_LOG(LogTemp, Warning, TEXT("ApplyDamage of APlayerCharacter"));

	bool isDead = Super::ApplyDamage();

	if (isDead) {

		FTimerHandle UnusedHandle;

		GetWorldTimerManager().SetTimer(
			UnusedHandle, this, &APlayerCharacter::RestartGame, 3.f, false);

	}

	return isDead;
}

void APlayerCharacter::RestartGame()
{

	// UE_LOG(LogTemp, Warning, TEXT("Player is Dead, Todo: Restart Game"));


	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

}
