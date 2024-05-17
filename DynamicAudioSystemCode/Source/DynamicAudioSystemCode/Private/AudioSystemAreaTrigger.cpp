// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioSystemAreaTrigger.h"

// Sets default values
AAudioSystemAreaTrigger::AAudioSystemAreaTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAudioSystemAreaTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAudioSystemAreaTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

USoundWave* AAudioSystemAreaTrigger::GetAreaTrack_Implementation()
{
	return mAreaTrack;
}
