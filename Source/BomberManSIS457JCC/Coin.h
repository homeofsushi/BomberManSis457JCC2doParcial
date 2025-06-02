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
 *   - Implementa InitializeBlock() para configurar mesh/colisión/rotación.
 *   - Implementa Clone() para el patrón Prototype.
 *   - Lógica de overlap que llama a Player->CollectCoin(this).
 */
UCLASS()
class BOMBERMANSIS457JCC_API ACoin : public ABloqueBase
{
    GENERATED_BODY()

public:
    ACoin();

    /** Cada frame rotaremos y haremos la animación “ping-pong” de la moneda. */
    virtual void Tick(float DeltaTime) override;

    /** Configura mesh, colisión, material según CoinType. */
    virtual void InitializeBlock() override;

    /** Devuelve un clon idéntico: se spawnea otra moneda en el mismo transform. */
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

    /** Valor numérico de la moneda (p. ej. cuánto puntaje o cuántas monedas da). */
    UPROPERTY(EditAnywhere, Category = "Coin")
    int32 CoinValue;

    /** Componente de mesh para la moneda. */
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* CoinMesh;

    /** Esfera de colisión para detectar overlap con el jugador. */
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* CollisionSphere;

    /** Velocidad de rotación en grados/segundo. */
    UPROPERTY(EditAnywhere, Category = "Coin")
    float RotationSpeed;

    /** Dirección (+1 o -1) para hacer un giro de ida y vuelta. */
    UPROPERTY(EditAnywhere, Category = "Coin")
    float RotationDirection;

    /** Temporizador para alternar dirección cada RotationInterval. */
    float RotationTimer;

    /** Intervalo en segundos para cambiar la dirección de rotación (ping-pong). */
    UPROPERTY(EditAnywhere, Category = "Coin")
    float RotationInterval;
};
