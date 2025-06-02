// Coin.cpp
#include "Coin.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "BomberManSIS457JCCCharacter.h"   // Tu clase de personaje, para CollectCoin()
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "UObject/SoftObjectPath.h"
#include "Materials/MaterialInterface.h"
#include "Engine/Engine.h"        // Para GEngine->AddOnScreenDebugMessage si quieres debug

ACoin::ACoin()
{
    // Queremos que Tick() se llame cada frame para rotar la moneda
    PrimaryActorTick.bCanEverTick = true;

    // 1) Creamos la esfera de colisi�n
    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    RootComponent = CollisionSphere;
    CollisionSphere->InitSphereRadius(100.f);
    CollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    // Vinculamos el evento de overlap
    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);

    // 2) Creamos el componente de malla
    CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMesh"));
    CoinMesh->SetupAttachment(RootComponent);

    // Cargamos un StaticMesh de StarterContent (vector cilindro)
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
        TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder")
    );
    if (MeshAsset.Succeeded())
    {
        CoinMesh->SetStaticMesh(MeshAsset.Object);
        CoinMesh->SetRelativeScale3D(FVector(1.5f, 1.5f, 0.3f));
        CoinMesh->SetRelativeRotation(FRotator(90.f, 90.f, 0.f));
    }

    // 3) Inicializamos valores de rotaci�n
    RotationSpeed = 45.f;   // grados por segundo
    RotationDirection = 1.f;    // comienza rotando �hacia adelante�
    RotationTimer = 0.f;
    RotationInterval = 1.0f;   // cambia de direcci�n cada 1 segundo

    // 4) Variables de tipo y valor de la moneda
    CoinType = ECoinType::Gold;
    CoinValue = 1;
}

void ACoin::BeginPlay()
{
    Super::BeginPlay();

    // En BeginPlay no colocamos mesh/material, sino en InitializeBlock().
    // De todos modos, si la moneda se spawnea manualmente sin f�brica, 
    // podemos llamar aqu� a InitializeBlock():
    InitializeBlock();
}

void ACoin::InitializeBlock()
{
    // Llamado por la f�brica justo despu�s de spawnear el actor.
    // 1) Configuramos el material seg�n el tipo de moneda:
    UMaterialInterface* CoinMaterial = nullptr;
    switch (CoinType)
    {
    case ECoinType::Gold:
        CoinMaterial = LoadObject<UMaterialInterface>(
            nullptr,
            TEXT("/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold")
        );
        break;
    case ECoinType::Silver:
        CoinMaterial = LoadObject<UMaterialInterface>(
            nullptr,
            TEXT("/Game/StarterContent/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel")
        );
        break;
    case ECoinType::Bronze:
        CoinMaterial = LoadObject<UMaterialInterface>(
            nullptr,
            TEXT("/Game/StarterContent/Materials/M_Metal_Rust.M_Metal_Rust")
        );
        break;
    default:
        break;
    }

    if (CoinMaterial && CoinMesh)
    {
        CoinMesh->SetMaterial(0, CoinMaterial);
    }

    // 2) Aseguramos que la colisi�n est� en OverlapAllDynamic
    if (CollisionSphere)
    {
        CollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    }
}

void ACoin::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Cada frame, actualizamos el temporizador
    RotationTimer += DeltaTime;
    if (RotationTimer >= RotationInterval)
    {
        // Cambiar la direcci�n (ping-pong)
        RotationDirection *= -1.f;
        RotationTimer = 0.f;
    }

    // Aplicar rotaci�n en Yaw
    if (CoinMesh)
    {
        FRotator CurrRot = CoinMesh->GetRelativeRotation();
        CurrRot.Yaw += RotationSpeed * RotationDirection * DeltaTime;
        CoinMesh->SetRelativeRotation(CurrRot);
    }
}

void ACoin::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    if (!OtherActor || OtherActor == this)
        return;

    // Si el overlapping actor es nuestro personaje, notificamos �CollectCoin�
    ABomberManSIS457JCCCharacter* Player = Cast<ABomberManSIS457JCCCharacter>(OtherActor);
    if (Player)
    {
        Player->CollectCoin(this);
        // Se supone que en tu Character implementas CollectCoin(ACoin*) y ah� haces Destroy()
        // o lo que necesites (sumar contador, UI, etc.).
    }
}

ABloqueBase* ACoin::Clone() const
{
    UWorld* World = GetWorld();
    if (!World)
        return nullptr;

    // 1) Obtenemos la transformaci�n actual del actor original
    FTransform OrigTransform = GetActorTransform();

    // 2) Spawneamos una nueva ACoin en esa transform
    ACoin* Clon = World->SpawnActor<ACoin>(ACoin::StaticClass(), OrigTransform);

    if (Clon)
    {
        // 3) Copiar las variables que sean importantes (tipo y valor)
        Clon->CoinType = this->CoinType;
        Clon->CoinValue = this->CoinValue;
        Clon->RotationSpeed = this->RotationSpeed;
        Clon->RotationDirection = this->RotationDirection;
        Clon->RotationInterval = this->RotationInterval;
        // ... (si tuvieras m�s propiedades a clonar, aqu� las copiar�as)

        // 4) Llamar a InitializeBlock() para que cargue el material seg�n CoinType
        Clon->InitializeBlock();
    }

    return Clon;
}

