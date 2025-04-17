#include "Pawns/Tower.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/Tank.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (InFireRange() && PlayerTank)
	{
		RotateTurret(PlayerTank->GetActorLocation());
	}
}

void ATower::CheckFireCondition()
{
	if (InFireRange())
		Fire();
}

bool ATower::InFireRange()
{
	if (PlayerTank)
	{
		float Distance = FVector::Dist(GetActorLocation(), PlayerTank->GetActorLocation());
		if (Distance <= FireRange)
			return true;
	}
	return false;
}


