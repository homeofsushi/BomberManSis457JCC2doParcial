// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueMadera.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

ABloqueMadera::ABloqueMadera()
{
    // Creamos y configuramos el componente de malla est�tica
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
    // Aqu� podr�as cambiar el material, la escala, u otra l�gica:
    // Por ejemplo:
    // UMaterialInterface* Mat = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/MaderaMat.MaderaMat"));
    // if (Mat && MeshComp) { MeshComp->SetMaterial(0, Mat); }

    // Tambi�n podr�as inicializar variables propias de "madera" (durabilidad, rigidez, etc.)
}

ABloqueBase* ABloqueMadera::Clone() const
{
    UWorld* World = GetWorld();
    if (!World) return nullptr;

    // Obtenemos la misma transform que el original
    FTransform T = GetActorTransform();

    // Spawneamos un nuevo BloqueMadera en esa transformaci�n
    ABloqueMadera* Copia = World->SpawnActor<ABloqueMadera>(ABloqueMadera::StaticClass(), T);
    if (Copia)
    {
        // Copia de propiedades internas (si las existieran):
        // Copia->Durabilidad = this->Durabilidad;
        // Copia->MeshComp->SetMaterial(0, MeshComp->GetMaterial(0));

        Copia->InitializeBlock();
    }
    return Copia;
}
