// Fill out your copyright notice in the Description page of Project Settings.
#include "BloqueLadrillo.h"

#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

ABloqueLadrillo::ABloqueLadrillo()
{
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshLadrillo"));
    RootComponent = MeshComp;

    // Mesh de cubo por defecto
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
    if (MeshAsset.Succeeded())
    {
        MeshComp->SetStaticMesh(MeshAsset.Object);
        MeshComp->SetRelativeScale3D(FVector(1.0f, 1.0f, 2.0f));
    }

    // Material de ladrillo (M_Brick_Clay)
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("Material'/Game/StarterContent/Materials/M_Brick_Clay_Beveled.M_Brick_Clay_Beveled'"));
    if (MaterialAsset.Succeeded())
    {
        MeshComp->SetMaterial(0, MaterialAsset.Object);
    }

    PrimaryActorTick.bCanEverTick = false;
}

void ABloqueLadrillo::InitializeBlock()
{
    // Aquí podrías ajustar más si quisieras—por ejemplo, cambio de escala o colisión.
}



