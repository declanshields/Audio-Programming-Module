// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"
#include "AudioSystemInterface.h"
#include "TimerManager.h"
#include "AudioSystemActorComponent.generated.h"


UCLASS( ClassGroup=(Audio), meta=(BlueprintSpawnableComponent) )
class DYNAMICAUDIOSYSTEMCODE_API UAudioSystemActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAudioSystemActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ActivateMixer();

	UFUNCTION(BlueprintCallable)
	void DeactivateMixer();

	UFUNCTION(BlueprintCallable)
	void FadeInTrack();

	UFUNCTION(BlueprintCallable)
	void FadeOutTrack();

	UFUNCTION(BlueprintCallable)
	void OnOwnerBeginOverlap(AActor* InOtherActor);

	UFUNCTION(BlueprintCallable)
	void OnOwnerEndOverlap();

	UFUNCTION(BlueprintCallable)
	void SetAllParameters(USoundWave* InTrackOne, USoundWave* InTrackTwo, float InFadeInTime, float InFadeOutTime,
		float InTrackTwoLevel, float InTrackOneGain, float InTrackTwoGain, float InOutputGain)
	{
		SetTrackParameters(InTrackOne, InTrackTwo);
		SetFadeParameters(InFadeInTime, InFadeOutTime, InTrackTwoLevel);
		SetGainParameters(InTrackOneGain, InTrackTwoGain, InOutputGain);
	}

	UFUNCTION(BlueprintCallable)
	void SetFadeParameters(float InFadeInTime, float InFadeOutTime, float InSecondTrackLevel)
	{
		mFadeInTime = InFadeInTime;
		mFadeOutTime = InFadeOutTime;
		mTrackTwoLevel = InSecondTrackLevel;

		if (mMixer)
		{
			if (!mMixer->IsPlaying())
				ActivateMixer();

			mMixer->SetFloatParameter(FName("Fade In Time"), mFadeInTime);
			mMixer->SetFloatParameter(FName("Fade Out Time"), mFadeOutTime);
			mMixer->SetFloatParameter(FName("Second Track Level"), mTrackTwoLevel);
		}
	}

	UFUNCTION(BlueprintCallable)
	void SetGainParameters(float InTrackOneGain, float InTrackTwoGain, float InOutputGain)
	{
		mTrackOneGain = InTrackOneGain;
		mTrackTwoGain = InTrackTwoGain;
		mOutputGain = InOutputGain;

		if (mMixer)
		{
			if (!mMixer->IsPlaying())
				ActivateMixer();

			mMixer->SetFloatParameter(FName("Main Track Gain"), mTrackOneGain);
			mMixer->SetFloatParameter(FName("Second Track Gain"), mTrackTwoGain);
			mMixer->SetFloatParameter(FName("Output Gain"), mOutputGain);
		}
	}

	UFUNCTION(BlueprintCallable)
	void SetTrackParameters(USoundWave* InTrackOne, USoundWave* InTrackTwo)
	{
		if (InTrackOne)
			mTrackOne = InTrackOne;
		if (InTrackTwo)
			mTrackTwo = InTrackTwo;

		if (mMixer)
		{
			if (!mMixer->IsPlaying())
				ActivateMixer();

			mMixer->SetWaveParameter(FName("Main Track"), mTrackOne);
			mMixer->SetWaveParameter(FName("Second Track"), mTrackTwo);
		}
	}

	UFUNCTION(BlueprintCallable)
	void StartMainTrack();

	UFUNCTION(BlueprintCallable)
	void SwitchTracks(USoundWave* InAreaTrack);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=MixerDetails)
	UAudioComponent* mMixer;

private:
	USoundWave* mTrackOne;
	USoundWave* mTrackTwo;

	float mFadeInTime;
	float mFadeOutTime;
	float mTrackTwoLevel;
	float mTrackOneGain;
	float mTrackTwoGain;
	float mOutputGain;
	bool bTrackFadedIn = false;
};
