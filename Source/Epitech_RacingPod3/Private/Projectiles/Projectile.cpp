#include "Projectiles/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundCue.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1000.f;
	ProjectileMovementComponent->InitialSpeed = 1000.f;

}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(5.f);
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = GetOwner();

	if (MyOwner == nullptr) return;

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);

		if (ExplosionSFX)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				ExplosionSFX,
				GetActorLocation());
		}
		
		if (ExplosionVFX)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				this,
				ExplosionVFX,
				GetActorLocation(),
				GetActorRotation());
		}
		
		Destroy();
	}
}
