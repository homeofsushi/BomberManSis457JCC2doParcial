// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueBase.h"

// Sets default values
ABloqueBase::ABloqueBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABloqueBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABloqueBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
 ABloqueBase * ABloqueBase::Clone(const FVector & NuevaPosicion)
{
    UWorld* World = GetWorld();
    if (!World) return nullptr;

    FActorSpawnParameters SpawnParams;
    ABloqueBase* NuevoBloque = World->SpawnActor<ABloqueBase>(GetClass(), NuevaPosicion, GetActorRotation(), SpawnParams);
    if (!NuevoBloque) return nullptr;

    // Copia propiedades relevantes
    NuevoBloque->TipoBloque = this->TipoBloque;
    NuevoBloque->SetActorScale3D(this->GetActorScale3D());
    NuevoBloque->SetActorRotation(this->GetActorRotation());
    // Copia materiales si es necesario, etc.

    return NuevoBloque;
}
 // BloqueBase.cpp
 void ABloqueBase::RecibirDanio(int32 Danio)
 {
     Dureza -= Danio;
     if (Dureza <= 0)
     {
         Destroy();
     }
 }



