// Fill out your copyright notice in the Description page of Project Settings.


#include "BombaSimple.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
ABombaSimple::ABombaSimple()
{

    PrimaryActorTick.bCanEverTick = true;
    UStaticMeshComponent* Malla = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaBomba"));
    RootComponent = Malla;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> EsferaMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
    if (EsferaMesh.Succeeded())
    {
        Malla->SetStaticMesh(EsferaMesh.Object);
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> OroMat(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel'"));
    if (OroMat.Succeeded())
    {
        Malla->SetMaterial(0, OroMat.Object);
    }
    Movimiento = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movimiento"));
    Movimiento->InitialSpeed = 600.f;
    Movimiento->MaxSpeed = 600.f;
    Movimiento->bRotationFollowsVelocity = true;
    Movimiento->ProjectileGravityScale = 0.f;
}

void ABombaSimple::BeginPlay()
{
    Super::BeginPlay();
    OnActorHit.AddDynamic(this, &ABombaSimple::OnHit);
}

void ABombaSimple::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    Explota();
}

void ABombaSimple::Explota()
{
    // Lógica de explosión aquí
    Destroy();
}
