// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoBase.h"

// Sets default values
AEnemigoBase::AEnemigoBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
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
	Moverse();
	Atacar();
	Volar();
	UsarHabilidadEspecial();
	Esconderse();
}

// Called to bind functionality to input
void AEnemigoBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

