// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// APÓS IMPORTAR DRAW DEBUG HELPERS VOCÊ CONSEGUE MANIPULAR O DRAW DEBUG PARA FAZER VARREDURAS E VERIFICAR COLISÕES

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr) {
		return;
	}
	
	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Display, TEXT("Grab grabber"));

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr) {
		return;
	}

	// DEFINE O LOCAL DE INICIO DA LINHA QUE SERÁ DESENHADA PELO DRAW DEBUG LINE, NESSE CASO PARA UTILIZARMOS O DRAW DEBUG PRECISAMOS DE UMA POSIÇÃO DE INICIO E UMA POSIÇÃO DE FIM 
	FVector Start = GetComponentLocation();
	// DEFINE O LOCAL FINAL DA LINHA QUE SERÁ DESENHADA PELO DRAW DEBUG LINE
	FVector End = Start + GetForwardVector() * MaxGrabDistance;

	// DESENHA A LINHA UTILIZANDO A FUNÇÃO APROPRIADA E OS ATRIBUTOS NECESSÁRIOS
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);

	// DEFINE UM RAIO PARA UMA ESFERA INVISIVEL
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	// DEFINE UMA VARIÁVEL DE CONTROLE PARA COLISÕES
	FHitResult HitResult;
	// UMA FUNÇÃO QUE RETORNA UM VALOR BOOL DE ACORDO COM A VERIFICAÇÃO DE COLISÃO
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);

	// VERIFICA SE O VALOR DE HASHIT É VERDADEIRO
	if (HasHit) {
		
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);

		/*DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Green, false, 5);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 5);

		/// SE O VALOR DE HASHIT FOR VERDADEIRO, ENTÃO HITACTOR RECEBE QUAL É O OBJETO QUE ESTÁ NA ÁREA DE COLISÃO
		AActor* HitActor = HitResult.GetActor();
		// DEFINE UMA VARIÁVEL QUE ARMAZENA O NOME DO OBJETO ACTOR QUE FOI ATINGIDO PELA VERIFICAÇÃO DE COLISÃO

		FString NameOrLabel = *HitActor->GetActorNameOrLabel();
		// PRINTA O NOME DO OBJETO NO LOG/CONSOLE
		UE_LOG(LogTemp, Display, TEXT("Name: %s"), *NameOrLabel);*/
	}
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Display, TEXT("Released grabber"));
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const {
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(Result == nullptr){
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent."));
	}
	return Result;
}