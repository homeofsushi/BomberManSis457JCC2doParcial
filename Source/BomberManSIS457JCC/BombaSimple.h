// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bomba.h"
#include "BombaSimple.generated.h"
class UProjectileMovementComponent;
UCLASS()
class BOMBERMANSIS457JCC_API ABombaSimple : public ABomba
{
	GENERATED_BODY()
public:
    ABombaSimple();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

    void Explota();

    UPROPERTY(VisibleAnywhere)
    UProjectileMovementComponent* Movimiento;
	
};
