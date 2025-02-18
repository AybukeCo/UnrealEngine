// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//TArray<AActor*> Actors;
	//GetOverlappingActors(Actors);

	//int32 index = 0;
	//while (index < Actors.Num())
	//{
	//	FString ActorName = Actors[index]->GetActorNameOrLabel();
	//	UE_LOG(LogTemp, Display, TEXT("Overlapping: %s"), *ActorName);
	//	++index;
	//}

	//how to write the while loop shorter with for loop like below:
	//for (int32 i = 0; i < Actors.Num(); i++)
	//{
	//	FString ActorName = Actors[i]->GetActorNameOrLabel();
	//	UE_LOG(LogTemp, Display, TEXT("Overlapping: %s"), *ActorName);
	//}

	//how to write the for loop above to range based for loop below:
	//for (AActor* Actor : Actors)
	//{
	//	FString ActorName = Actor->GetActorNameOrLabel();
	//
	//	if (Actor->ActorHasTag("Unlock1")) 
	//	{
	//		UE_LOG(LogTemp, Display, TEXT("Unlocking: %s"), *ActorName);
	//	}
	//	UE_LOG(LogTemp, Display, TEXT("Overlapping: %s"), *ActorName);
	//}

	if (Mover == nullptr)
    {
        return;
    }

    AActor* Actor = GetAcceptableActor();
    if (Actor != nullptr)
    {
        UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
        if (Component != nullptr)
        {
            Component->SetSimulatePhysics(false);
        }
        Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
        Mover->SetShouldMove(true);
    }
    else
    {
        Mover->SetShouldMove(false);
    }
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
    Mover = NewMover;
}


AActor* UTriggerComponent::GetAcceptableActor() const
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
    for (AActor* Actor : Actors)
    {
        bool HasAcceptableTag = Actor->ActorHasTag(AcceptableActorTag);
        bool IsGrabbed = Actor->ActorHasTag("Grabbed");
        if (HasAcceptableTag && !IsGrabbed)
        {
            return Actor;
        }
    }

    return nullptr;
}
