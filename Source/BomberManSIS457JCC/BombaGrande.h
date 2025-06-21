// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bomba.h"
#include "BombaGrande.generated.h"

class UProjectileMovementComponent;
UCLASS()
class BOMBERMANSIS457JCC_API ABombaGrande : public ABomba
{
	GENERATED_BODY()
public:
    ABombaGrande();

    virtual void Tick(float DeltaTime) override;

protected:
    void Explota();

    UPROPERTY(VisibleAnywhere)
    UProjectileMovementComponent* Movimiento;

    float EscalaObjetivo;
	
};
