#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGWallAttachmentHologram.h"
#include "PPPowerPoleHologram.generated.h"


namespace PAxis
{
	enum Type
	{
		None,
		Pich,
		Yaw,
		Roll,
	};
}


UCLASS()
class POWERPOLES_API APPPowerPoleHologram : public AFGWallAttachmentHologram
{
	GENERATED_BODY()

public:
	APPPowerPoleHologram();
	FORCEINLINE ~APPPowerPoleHologram() = default;

	virtual void BeginPlay() override;
	virtual void SetHologramLocationAndRotation(const FHitResult& hitResult) override;
	virtual bool TrySnapToActor(const FHitResult& hitResult) override;
	virtual void CheckValidFloor() override;
	virtual void CheckClearance() override;

private:
	bool Foundation;

protected:
	void rotateComponent(USceneComponent* component, FRotator rotate);
	void setComponentLocation(USceneComponent* component, FVector location);

	USceneComponent* powerPoleMesh = nullptr;
	USceneComponent* powerConnection = nullptr;

	FVector newLocation;
};
