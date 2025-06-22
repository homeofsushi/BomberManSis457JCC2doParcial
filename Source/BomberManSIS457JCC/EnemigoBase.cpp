// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoBase.h"
#include "CommandMover.h"
#include "CommandAtacar.h"

// Sets default values
AEnemigoBase::AEnemigoBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	// Esta línea asegura que el enemigo siempre tenga un AIController
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AEnemigoBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemigoBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickComportamiento();

}
void AEnemigoBase::TickComportamiento()
{
	BuscarJugador();

	if (Objetivo && FVector::Dist(GetActorLocation(), Objetivo->GetActorLocation()) < 250.0f)
	{
		ICommand* Comando = new CommandAtacar(this);
		Comando->Ejecutar();
		delete Comando;
	}
	else if (Objetivo)
	{
		ICommand* Comando = new CommandMover(this);
		Comando->Ejecutar();
		delete Comando;
	}

	Volar();
	UsarHabilidadEspecial();
	Esconderse();
}

// Called to bind functionality to input
void AEnemigoBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

