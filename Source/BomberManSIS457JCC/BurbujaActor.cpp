// Fill out your copyright notice in the Description page of Project Settings.


#include "BurbujaActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABurbujaActor::ABurbujaActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    CollisionComponent->InitSphereRadius(20.0f);
    CollisionComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
    RootComponent = CollisionComponent;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    CollisionComponent->OnComponentHit.AddDynamic(this, &ABurbujaActor::OnHit);
   
    static ConstructorHelpers::FObjectFinder<UStaticMesh> BubbleMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
    if (BubbleMesh.Succeeded())
    {
        MeshComponent->SetStaticMesh(BubbleMesh.Object);
        MeshComponent->SetRelativeScale3D(FVector(0.5f));
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> BubbleMaterial(TEXT("/Game/StarterContent/Materials/M_Water_Ocean.M_Water_Ocean"));
    if (BubbleMaterial.Succeeded())
    {
        MeshComponent->SetMaterial(0, BubbleMaterial.Object);
    }

    InitialLifeSpan = 3.0f; // Se destruye después de 3 segundos

}

// Called when the game starts or when spawned
void ABurbujaActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABurbujaActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    // Mueve la burbuja hacia adelante
    FVector Forward = GetActorForwardVector();
    SetActorLocation(GetActorLocation() + Forward * Speed * DeltaTime);

}
void ABurbujaActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Aquí puedes aplicar daño o efectos al jugador u otros actores
    Destroy();
}

