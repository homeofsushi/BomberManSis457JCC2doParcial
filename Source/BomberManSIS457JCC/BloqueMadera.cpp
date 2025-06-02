// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueMadera.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

ABloqueMadera::ABloqueMadera()
{
    // Creamos y configuramos el componente de malla estática
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshMadera"));
    RootComponent = MeshComp;

    // Cargar malla predeterminada de cubo (Shape_Cube) en el constructor
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
    if (Mesh.Succeeded())
    {
        MeshComp->SetStaticMesh(Mesh.Object);
        MeshComp->SetRelativeScale3D(FVector(1.0f, 1.0f, 2.0f));
    }

    // Cargar material para el acero (M_Metal_Steel)
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("Material'/Game/StarterContent/Materials/M_Wood_Oak.M_Wood_Oak'"));
    if (Material.Succeeded())
    {
        MeshComp->SetMaterial(0, Material.Object);
    }
}

void ABloqueMadera::InitializeBlock()
{
    // Aquí podrías cambiar el material, la escala, u otra lógica:
    // Por ejemplo:
    // UMaterialInterface* Mat = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/MaderaMat.MaderaMat"));
    // if (Mat && MeshComp) { MeshComp->SetMaterial(0, Mat); }

    // También podrías inicializar variables propias de "madera" (durabilidad, rigidez, etc.)
}


