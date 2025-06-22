#include "EnemigoTerrestre.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BomberManSIS457JCCCharacter.h"

AEnemigoTerrestre::AEnemigoTerrestre()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Trim_90_In.Shape_Trim_90_In"));
    if (MeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(MeshAsset.Object);
        MeshComponent->SetRelativeScale3D(FVector(1.0f));
    }

    // Asigna un material simple
    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/StarterContent/Materials/M_Metal_Rust.M_Metal_Rust"));
    if (MaterialAsset.Succeeded())
    {
        MeshComponent->SetMaterial(0, MaterialAsset.Object);
    }

}
void AEnemigoTerrestre::BuscarJugador()
{
    Objetivo = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AEnemigoTerrestre::Moverse()
{
    if (Objetivo)
    {
        float Distancia = FVector::Dist(GetActorLocation(), Objetivo->GetActorLocation());
        if (Distancia > 200.0f) // Solo moverse si está lejos
        {
            FVector Direccion = (Objetivo->GetActorLocation() - GetActorLocation()).GetSafeNormal();
            AddMovementInput(Direccion, 1.0f);
        }
    }
}

void AEnemigoTerrestre::Atacar()
{
    if (Objetivo && FVector::Dist(GetActorLocation(), Objetivo->GetActorLocation()) < 200.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("¡Enemigo terrestre ataca al jugador!"));
    }
}

void AEnemigoTerrestre::Esconderse()
{
    if (Vida < 20.0f)
    {
        SetActorHiddenInGame(true);
    }
}