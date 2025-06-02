// Fill out your copyright notice in the Description page of Project Settings.


#include "ALaberinto.h"

// Sets default values
AALaberinto::AALaberinto()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AALaberinto::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AALaberinto::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AALaberinto::InicializarMatriz(int Filas, int Columnas)
{
    MatrizBloques.SetNum(Filas);
    for (int i = 0; i < Filas; ++i)
    {
        MatrizBloques[i].SetNum(Columnas);
        for (int j = 0; j < Columnas; ++j)
        {
            MatrizBloques[i][j] = nullptr;
        }
    }
}

