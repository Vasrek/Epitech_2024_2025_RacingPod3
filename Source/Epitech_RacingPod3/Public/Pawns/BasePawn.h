#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

// last include
#include "BasePawn.generated.h"

class UNiagaraSystem;
class AProjectile;
class UBoxComponent;
class USoundCue;

UCLASS()
class EPITECH_RACINGPOD3_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float TurnRate = 45.f;

	void RotateTurret(FVector LookAtTarget);

	UPROPERTY(EditAnywhere, Category = "Canon properties")
	float InterpSpeed = 5.f;

	void Fire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Combat properties")
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat properties")
	FVector ProjectileScale = FVector(2.0f, 2.0f, 2.0f);

	UPROPERTY(EditAnywhere, Category = "Combat properties")
	USoundCue* FireSFX;

	UPROPERTY(EditAnywhere, Category = "Combat properties")
	UNiagaraSystem* FireVFX;

};
