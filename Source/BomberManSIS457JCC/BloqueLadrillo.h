// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BloqueBase.h"
#include "BloqueLadrillo.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANSIS457JCC_API ABloqueLadrillo : public ABloqueBase
{
	GENERATED_BODY()

public:
    ABloqueLadrillo();

    virtual void InitializeBlock() override;

private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComp;
	
};
