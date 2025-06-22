// Fill out your copyright notice in the Description page of Project Settings.


#include "BombaSimple.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "BloqueBase.h"
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

    Danio = 10;
    RadioExplosion = 200.f;
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
    // Encuentra bloques dentro del radio
    TArray<AActor*> BloquesAfectados;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABloqueBase::StaticClass(), BloquesAfectados);

    // Crear un composite para los bloques afectados
    ABloqueComposite* Grupo = GetWorld()->SpawnActor<ABloqueComposite>();

    for (AActor* Bloque : BloquesAfectados)
    {
        if (FVector::Dist(Bloque->GetActorLocation(), GetActorLocation()) <= RadioExplosion)
        {
            IBloqueComponent* BloqueComp = Cast<IBloqueComponent>(Bloque);
            if (BloqueComp)
            {
                Grupo->AgregarHijo(TScriptInterface<IBloqueComponent>(Bloque));
            }
        }
    }

    // Aplicar da�o a todos los hijos del composite
    Grupo->RecibirDanio(Danio);

    // Si el grupo solo se usa para la explosi�n, puedes destruirlo despu�s
    Grupo->Destroy();

    Destroy();
}
