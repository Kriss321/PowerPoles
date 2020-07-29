// ILikeBanas

#pragma once

#include "FGPowerConnectionComponent.h"
#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "PPBuildablePole.generated.h"


/**
 * 
 */
UCLASS( Abstract )
class POWERPOLES_API APPBuildablePole : public AFGBuildable
{
	GENERATED_BODY()
	
public:
	APPBuildablePole();
	FORCEINLINE ~APPBuildablePole() = default;

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	//virtual void PreLoadGame(int32 saveVersion, int32 gameVersion) override;

	UPROPERTY(SaveGame, Replicated)
	FVector addLocation = FVector(0, 0, 0);
		//float mLength = 0;

	/** Set the pole's height. */
	void setPole2Location(FVector location);

	UPROPERTY(VisibleAnywhere, Category = "Pole")
	class UStaticMeshComponent* mPowerPole1;

	UPROPERTY(VisibleAnywhere, Category = "Pole")
	class UStaticMeshComponent* mPowerPole2;

	UPROPERTY(VisibleAnywhere, Category = "Pole")
	class UFGPowerConnectionComponent* mPowerConnection1;

	UPROPERTY(VisibleAnywhere, Category = "Pole")
	class UFGPowerConnectionComponent* mPowerConnection2;

	UPROPERTY(VisibleAnywhere, Category = "Pole")
	class UFGPowerConnectionComponent* mHiddenPowerConnection;
};
