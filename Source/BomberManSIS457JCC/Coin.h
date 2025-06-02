// Coin.h
#pragma once

#include "CoreMinimal.h"
#include "BloqueBase.h"                        // Ahora hereda de ABloqueBase
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Coin.generated.h"

/**
 * ECoinType
 *
 *   - Enum de tipos de moneda (oro, plata, bronce).
 */
UENUM(BlueprintType)
enum class ECoinType : uint8
{
    Gold     UMETA(DisplayName = "Gold"),
    Silver   UMETA(DisplayName = "Silver"),
    Bronze   UMETA(DisplayName = "Bronze"),
};

/**
 * ACoin (ConcreteProduct)
 *
 *   - Hereda de ABloqueBase.
 *   - Implementa InitializeBlock() para configurar mesh/colisi�n/rotaci�n.
 *   - Implementa Clone() para el patr�n Prototype.
 *   - L�gica de overlap que llama a Player->CollectCoin(this).
 */
UCLASS()
class BOMBERMANSIS457JCC_API ACoin : public ABloqueBase
{
    GENERATED_BODY()

public:
    ACoin();

    /** Cada frame rotaremos y haremos la animaci�n �ping-pong� de la moneda. */
    virtual void Tick(float DeltaTime) override;

    /** Configura mesh, colisi�n, material seg�n CoinType. */
    virtual void InitializeBlock() override;

    /** Devuelve un clon id�ntico: se spawnea otra moneda en el mismo transform. */
    virtual ABloqueBase* Clone() const override;

protected:
    /** Invocado cuando comienza el juego o se spawnea el actor. */
    virtual void BeginPlay() override;

    /** Maneja el evento de overlap con el jugador. */
    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );
public:
    /** Tipo de moneda (oro, plata, bronce). */
    UPROPERTY(EditAnywhere, Category = "Coin")
    ECoinType CoinType;
private:

    /** Valor num�rico de la moneda (p. ej. cu�nto puntaje o cu�ntas monedas da). */
    UPROPERTY(EditAnywhere, Category = "Coin")
    int32 CoinValue;

    /** Componente de mesh para la moneda. */
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* CoinMesh;

    /** Esfera de colisi�n para detectar overlap con el jugador. */
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* CollisionSphere;

    /** Velocidad de rotaci�n en grados/segundo. */
    UPROPERTY(EditAnywhere, Category = "Coin")
    float RotationSpeed;

    /** Direcci�n (+1 o -1) para hacer un giro de ida y vuelta. */
    UPROPERTY(EditAnywhere, Category = "Coin")
    float RotationDirection;

    /** Temporizador para alternar direcci�n cada RotationInterval. */
    float RotationTimer;

    /** Intervalo en segundos para cambiar la direcci�n de rotaci�n (ping-pong). */
    UPROPERTY(EditAnywhere, Category = "Coin")
    float RotationInterval;
};
