// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoAereo.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AEnemigoAereo::AEnemigoAereo()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Wedge_A.Shape_Wedge_A"));
    if (MeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(MeshAsset.Object);
        MeshComponent->SetRelativeScale3D(FVector(1.0f));
    }

    // Asigna un material simple
    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/StarterContent/Materials/M_Wood_Walnut.M_Wood_Walnut"));
    if (MaterialAsset.Succeeded())
    {
        MeshComponent->SetMaterial(0, MaterialAsset.Object);
    }

}
void AEnemigoAereo::BuscarJugador()
{
    Objetivo = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AEnemigoAereo::Moverse()
{
    if (Objetivo)
    {
        FVector Direccion = (Objetivo->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        AddMovementInput(Direccion, 1.0f);
    }
}

void AEnemigoAereo::Atacar()
{
    if (Objetivo && FVector::Dist(GetActorLocation(), Objetivo->GetActorLocation()) < 300.0f)
    {
        // Lógica de ataque aéreo
    }
}

void AEnemigoAereo::Volar()
{
    FVector Pos = GetActorLocation();
    Pos.Z = 300.0f;
    SetActorLocation(Pos);
}