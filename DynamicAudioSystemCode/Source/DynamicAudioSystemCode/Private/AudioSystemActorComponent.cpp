// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioSystemActorComponent.h"
#include "Components/CapsuleComponent.h"
#include "AudioSystemAreaTrigger.h"

// Sets default values for this component's properties
UAudioSystemActorComponent::UAudioSystemActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAudioSystemActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAudioSystemActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAudioSystemActorComponent::ActivateMixer()
{
	if (mMixer)
	{
		if (!mMixer->IsActive())
			mMixer->Activate();

		if (!mMixer->IsPlaying())
			mMixer->Play();
	}

	bTrackFadedIn = false;
}

void UAudioSystemActorComponent::DeactivateMixer()
{
	if (mMixer)
	{
		if (mMixer->IsPlaying())
			mMixer->Stop();

		mMixer->Deactivate();
	}
	bTrackFadedIn = false;
}

void UAudioSystemActorComponent::FadeInTrack()
{
	if (mMixer)
	{
		if (!mMixer->IsActive() || !mMixer->IsPlaying())
			ActivateMixer();

		mMixer->SetTriggerParameter(FName("Fade In"));
		bTrackFadedIn = true;

		mMixer->SetTriggerParameter(FName("Stop Main Track"));
	}
}

void UAudioSystemActorComponent::FadeOutTrack()
{
	if (mMixer && bTrackFadedIn)
	{
		if (!mMixer->IsActive() || !mMixer->IsPlaying())
			return;

		mMixer->SetTriggerParameter(FName("Play Main Track"));
		mMixer->SetTriggerParameter(FName("Fade Out"));
		bTrackFadedIn = false;
	}
}

void UAudioSystemActorComponent::StartMainTrack()
{
	if (mMixer)
	{
		ActivateMixer();

		mMixer->SetTriggerParameter(FName("Play Main Track"));
		bTrackFadedIn = false;
	}
}

void UAudioSystemActorComponent::OnOwnerBeginOverlap(AActor* InOtherActor)
{
	if (!mMixer->IsActive())
	{
		ActivateMixer();
	}

	if (InOtherActor)
	{
		IAudioSystemInterface* AudioInterface = Cast<IAudioSystemInterface>(InOtherActor);

		if (AudioInterface)
		{
			USoundWave* AreaTrack = AudioInterface->Execute_GetAreaTrack(InOtherActor);
			SwitchTracks(AreaTrack);
		}
		else
			return;
	}
}

void UAudioSystemActorComponent::OnOwnerEndOverlap()
{
	if (!GetOwner())
		return;

	if (!GetOwner()->GetComponentByClass<UCapsuleComponent>())
		return;

	TArray<AActor*> OverlappingActors;

	GetOwner()->GetComponentByClass<UCapsuleComponent>()->GetOverlappingActors(OverlappingActors, AAudioSystemAreaTrigger::StaticClass());

	USoundWave* MajorSoundZoneTrack = nullptr;
	int SoundZones = 0;

	if (!OverlappingActors.IsEmpty())
	{
		for (AActor* CollidingActor : OverlappingActors)
		{
			if (AAudioSystemAreaTrigger* Trigger = Cast<AAudioSystemAreaTrigger>(CollidingActor))
			{
				IAudioSystemInterface* AudioInterface = Cast<IAudioSystemInterface>(Trigger);
				SoundZones++;
				if (Trigger->GetIsMajorArea())
				{
					MajorSoundZoneTrack = AudioInterface->Execute_GetAreaTrack(Trigger);
				}
			}
		}
	}

	if (SoundZones == 1 && MajorSoundZoneTrack)
	{
		SwitchTracks(MajorSoundZoneTrack);
	}
	else if (SoundZones == 0)
	{
		bTrackFadedIn = false;

		if (mMixer)
		{
			mMixer->SetTriggerParameter(FName("Stop Tracks"));
			SetTrackParameters(nullptr, nullptr);
			DeactivateMixer();
		}
	}
}

void UAudioSystemActorComponent::SwitchTracks(USoundWave* InAreaTrack)
{
	if (mMixer && InAreaTrack)
	{
		if (!mTrackOne && !mTrackTwo)
		{
			bTrackFadedIn = false;
			SetTrackParameters(InAreaTrack, mTrackTwo);
			StartMainTrack();
		}
		else
		{
			if (bTrackFadedIn)
			{
				SetTrackParameters(InAreaTrack, mTrackTwo);
				mMixer->SetTriggerParameter(FName("Play Main Track"));
				FadeOutTrack();
			}
			else
			{
				SetTrackParameters(mTrackOne, InAreaTrack);
				FadeInTrack();
			}
		}
	}
}