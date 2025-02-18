// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//AActor* Owner = GetOwner(); //this is a pointer to get the address of Owner
	//FString Name = Owner->GetActorNameOrLabel(); 
	//if we have got a pointer, we use this arrow (->) operator
	//FVector OwnerLocation = Owner->GetActorLocation();
	//but if we are using a struct like an FString or FVector, we use the dot (.) operator
	//FString OwnerLocationString = OwnerLocation.ToCompactString();

	//UE_LOG(LogTemp, Display, TEXT("Mover Owner Address: %u"), Owner);
	//UE_LOG(LogTemp, Display, TEXT("Mover Owner: %s with location %s"), *Name, *OwnerLocationString);
	
	//float MyFloat = 5;
	//float* YourFloat = &MyFloat; //we put * after the type to declare that its a pointer
	//but we cannot ulog yourfloat because its a pointer; not a float 
	//float FloatValue = *YourFloat; //Here we make the pointer into a float, *pointer means get me the value at this location 
	//and to do that we put * before the pointer to de-reference it
	//which a symbol used in programming languages to access the value stored at the memory address pointed to by a pointer

	//UE_LOG(LogTemp, Display, TEXT("YourFloat Value: %f"), FloatValue);

	FVector TargetLocation = OriginalLocation;
	if (ShouldMove)
	{
		TargetLocation = OriginalLocation + MoveOffset;
	}
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	float Speed = MoveOffset.Length() / MoveTime;

	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	GetOwner()->SetActorLocation(NewLocation);


}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}


