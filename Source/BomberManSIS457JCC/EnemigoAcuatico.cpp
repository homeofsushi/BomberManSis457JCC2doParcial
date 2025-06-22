// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoAcuatico.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "BurbujaActor.h"

AEnemigoAcuatico::AEnemigoAcuatico()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_QuadPyramid.Shape_QuadPyramid"));
    if (MeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(MeshAsset.Object);
        MeshComponent->SetRelativeScale3D(FVector(1.0f));
    }

    // Asigna un material simple
    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/StarterContent/Materials/M_Water_Ocean.M_Water_Ocean"));
    if (MaterialAsset.Succeeded())
    {
        MeshComponent->SetMaterial(0, MaterialAsset.Object);
    }
    BurbujaClass = ABurbujaActor::StaticClass();
}
void AEnemigoAcuatico::BuscarJugador()
{
    Objetivo = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AEnemigoAcuatico::Moverse()
{
    if (Objetivo)
    {
        FVector Direccion = (Objetivo->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        AddMovementInput(Direccion, 1.0f);
    }
}

void AEnemigoAcuatico::Atacar()
{
    if (Objetivo && FVector::Dist(GetActorLocation(), Objetivo->GetActorLocation()) < 250.0f)
    {
        UsarHabilidadEspecial(); //Va a lanzar una burbuja fea
    }
}
void AEnemigoAcuatico::UsarHabilidadEspecial()
{
    // Ejemplo: Spawnea una burbuja frente al enemigo
    if (bPuedeLanzarBurbuja && Objetivo && BurbujaClass)
    {
        FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
        FRotator SpawnRotation = (Objetivo->GetActorLocation() - GetActorLocation()).Rotation();
        GetWorld()->SpawnActor<ABurbujaActor>(BurbujaClass, SpawnLocation, SpawnRotation);

        bPuedeLanzarBurbuja = false;
        GetWorld()->GetTimerManager().SetTimer(
            TimerHandle_BurbujaCooldown,
            this,
            &AEnemigoAcuatico::ReiniciarCooldownBurbuja,
			5.0f, // Es para que cada 5 segundos pueda lanzar otra burbuja
            false
        );
    }
}

void AEnemigoAcuatico::ReiniciarCooldownBurbuja()
{
    bPuedeLanzarBurbuja = true;
}
