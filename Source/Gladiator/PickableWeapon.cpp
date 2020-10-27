// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableWeapon.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"

APickableWeapon::APickableWeapon() {

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMesh"));
	SkeletalMesh->AttachToComponent(SphereCollision, FAttachmentTransformRules::KeepRelativeTransform);

	DamageBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Box"));
	DamageBox->AttachToComponent(SphereCollision, FAttachmentTransformRules::KeepRelativeTransform);


}

void APickableWeapon::BeginPlay()
{
}

UBoxComponent* APickableWeapon::GetDamageBox() const
{
	return nullptr;
}
