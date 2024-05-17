// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioSystemInterface.h"
#include "AudioSystemAreaTrigger.generated.h"

UCLASS()
class DYNAMICAUDIOSYSTEMCODE_API AAudioSystemAreaTrigger : public AActor, public IAudioSystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAudioSystemAreaTrigger();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	USoundWave* GetAreaTrack();
	virtual USoundWave* GetAreaTrack_Implementation() override;

	UFUNCTION(BlueprintCallable)
	bool GetIsMajorArea() { return mIsMajorArea; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=AreaTrack)
	USoundWave* mAreaTrack;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=AreaTrack)
	bool mIsMajorArea;
};
