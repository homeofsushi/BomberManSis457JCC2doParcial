// Fill out your copyright notice in the Description page of Project Settings.

#include "BloqueAcero.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

ABloqueAcero::ABloqueAcero()
{
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshAcero"));
    RootComponent = MeshComp;

    // Mesh de cubo por defecto
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
    if (MeshAsset.Succeeded())
    {
        MeshComp->SetStaticMesh(MeshAsset.Object);
        MeshComp->SetRelativeScale3D(FVector(1.0f, 1.0f, 2.0f));
    }

    // Material de acero (M_Metal_Steel)
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel'"));
    if (MaterialAsset.Succeeded())
    {
        MeshComp->SetMaterial(0, MaterialAsset.Object);
    }

    PrimaryActorTick.bCanEverTick = false;
}

void ABloqueAcero::InitializeBlock()
{
    // Ejemplo: podrías ajustar colisión o fisicas especiales.
}

ABloqueBase* ABloqueAcero::Clone() const
{
    UWorld* World = GetWorld();
    if (!World) return nullptr;

    FTransform T = GetActorTransform();
    ABloqueAcero* Clon = World->SpawnActor<ABloqueAcero>(ABloqueAcero::StaticClass(), T);
    if (Clon)
    {
        Clon->InitializeBlock();
    }
    return Clon;
}

