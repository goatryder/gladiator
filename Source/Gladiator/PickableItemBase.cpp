// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableItemBase.h"

// Sets default values
APickableItemBase::APickableItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickableItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickableItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APickableItemBase::AttachItemTo(USkeletalMeshComponent* meshRoot, FName socket)
{

	if (IsUsed)
		return false;

	AttachToComponent(meshRoot, FAttachmentTransformRules::KeepRelativeTransform, socket);

	SetActorRelativeLocation(FVector::ZeroVector);

	SetActorRelativeRotation(FRotator::ZeroRotator);

	IsUsed = true;

	return true;
}

