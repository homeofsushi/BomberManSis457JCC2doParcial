// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BloqueBase.h"
#include "BloqueMadera.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANSIS457JCC_API ABloqueMadera : public ABloqueBase
{
	GENERATED_BODY()

public:
    ABloqueMadera();

    virtual void InitializeBlock() override;


private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComp;
	
};
