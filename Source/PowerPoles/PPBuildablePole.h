// ILikeBanas

#pragma once

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
	virtual void BeginPlay() override;

	/** Set the pole's height. */
	void setPole2Location(FVector location);

	UPROPERTY(VisibleAnywhere, Category = "Pole")
	class UStaticMeshComponent* mPowerPole1;

	UPROPERTY(VisibleAnywhere, Category = "Pole")
	class UStaticMeshComponent* mPowerPole2;

	UPROPERTY(VisibleAnywhere, Category = "Pole")
	class USceneComponent* mPowerConnection1;

	UPROPERTY(VisibleAnywhere, Category = "Pole")
	class USceneComponent* mPowerConnection2;
};
