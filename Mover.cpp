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

	// GUARDA A POSIÇÃO ORIGINAL DO OBJETO NO MUNDO
	OriginalLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldMove) {
		// GUARDA A POSIÇÃO ATUAL DO OBJETO NO MUNDO
		FVector CurrentLocation = GetOwner()->GetActorLocation();

		// DEFINE UMA POSIÇÃO DE DESTINO PARA O QUAL O OBJETO PODE SE MOVER
		FVector TargetLocation = OriginalLocation + MoveOffset;

		// DEFINE A VELOCIDADE DO OBJETO PARA SE MOVER ATE O DESTINO
		float Speed = FVector::Distance(OriginalLocation, TargetLocation) / MoveTime;

		// REALIZA O CALCULO PARA MOVER O OBJETO ATÉ O DESTINO
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

		// DEFINE O NOVO LOCAL PARA O OBJETO NO MUNDO
		GetOwner()->SetActorLocation(NewLocation);
	}






	/*AActor* Owner = GetOwner();
	FString Name = Owner->GetActorNameOrLabel();
	UE_LOG(LogTemp, Display, TEXT("Mover Owner: %s"), *Name);

	// Este código abaixo obtem as Localizações do Vector 3D do objeto na cena e imprime no Log,
	// para que isso seja possível é necessério que o dados sejam convertidos para String
	FVector OwnerLocation = Owner->GetActorLocation();
	FString OwnerLocationString = OwnerLocation.ToCompactString();
	UE_LOG(LogTemp, Display, TEXT("Location is: %s"), *OwnerLocationString);*/

	// É EXTREMAMENTE IMPORTANTE aprender sobre ponteiros e endereços de memória pois com essas informações
	// serei capaz de criar games MAIS OTIMIZADOS utilizando técnicas que favorecem o desempenho
}

