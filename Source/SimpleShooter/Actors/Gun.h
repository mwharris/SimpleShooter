#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	AGun();
	virtual void Tick(float DeltaTime) override;
	void PullTrigger();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* RootSceneComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* MeshComponent;
	
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* MuzzleSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* ImpactParticle;
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float MaxRange = 5000.f;
	UPROPERTY(EditAnywhere, Category = "Properties")
	float Damage = 10.f;

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);
	AController* GetOwnerController() const;

};
