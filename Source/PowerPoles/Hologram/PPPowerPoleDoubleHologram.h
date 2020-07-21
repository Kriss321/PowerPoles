// ILikeBanas

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGWallAttachmentHologram.h"
#include "PPPowerPoleHologram.h"
#include "PPPowerPoleDoubleHologram.generated.h"


UCLASS()
class POWERPOLES_API APPPowerPoleDoubleHologram : public APPPowerPoleHologram
{
	GENERATED_BODY()

public:
	APPPowerPoleDoubleHologram();
	FORCEINLINE ~APPPowerPoleDoubleHologram() = default;

	virtual void BeginPlay() override;
	virtual void SetHologramLocationAndRotation(const FHitResult& hitResult) override;
	virtual bool TrySnapToActor(const FHitResult& hitResult) override;
	virtual void CheckClearance() override;

	virtual AActor* Construct(TArray< AActor* >& out_children, FNetConstructionID netConstructionID) override;

private:
	USceneComponent* powerPoleMesh2 = nullptr;
	USceneComponent* powerConnection2 = nullptr;
	
};