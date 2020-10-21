#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;
class ASimpleShooterGameModeBase;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AShooterCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	void Shoot();

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 10; 
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;
	UPROPERTY(VisibleAnywhere)
	float Health = 0.f;
	UPROPERTY()
	AGun* Gun;

	ASimpleShooterGameModeBase* GameModeRef;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void ControllerLookUp(float AxisValue);
	void ControllerLookRight(float AxisValue);
	void UpdateHUDHealth() const;

};