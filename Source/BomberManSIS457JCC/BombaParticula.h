// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bomba.h"
#include "BombaParticula.generated.h"
class UProjectileMovementComponent;
class UParticleSystem;
/**
 * 
 */
UCLASS()
class BOMBERMANSIS457JCC_API ABombaParticula : public ABomba
{
	GENERATED_BODY()
public:
    ABombaParticula();

protected:
    virtual void BeginPlay() override;
    UFUNCTION()
    void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);


    void Explota();

    UPROPERTY(VisibleAnywhere)
    UProjectileMovementComponent* Movimiento;

    UPROPERTY(EditDefaultsOnly, Category = "Efectos")
    UParticleSystem* ParticulasExplosion;
	
};
