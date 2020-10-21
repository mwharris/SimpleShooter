#pragma once

#include "CoreMinimal.h"
#include "SimpleShooter/SimpleShooterGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

UCLASS()
class SIMPLESHOOTER_API AKillEmAllGameMode : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()
	
public:
	void PawnKilled(APawn* KilledPawn) override;

private:
	void EndGame(bool bIsPlayerWinner);
	bool CheckWinCondition() const;
	
};
