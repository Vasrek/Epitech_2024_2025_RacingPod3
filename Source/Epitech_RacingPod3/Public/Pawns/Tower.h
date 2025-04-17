#pragma once

#include "CoreMinimal.h"
#include "Pawns/BasePawn.h"
#include "Tower.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class EPITECH_RACINGPOD3_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ATank* PlayerTank;

	UPROPERTY(EditAnywhere, Category = "Fire")
	float FireRange = 300.f;

	UPROPERTY(EditAnywhere, Category = "Fire")
	float FireRate = 2.f;

	FTimerHandle FireRateTimerHandle;

	void CheckFireCondition();

	bool InFireRange();
	
};
