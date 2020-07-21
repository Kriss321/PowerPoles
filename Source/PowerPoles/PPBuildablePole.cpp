// ILikeBanas


#include "PPBuildablePole.h"

#include "util/Logging.h"

void APPBuildablePole::BeginPlay() {
	Super::BeginPlay();
	TArray<USceneComponent*> components;
	this->GetRootComponent()->GetChildrenComponents(false, components);
	for (auto component : components) {
		if (component->GetName() == "PowerPole") {
			mPowerPole1 = Cast<UStaticMeshComponent>(component);
		}
		else if (component->GetName() == "PowerPole2") {
			mPowerPole2 = Cast<UStaticMeshComponent>(component);
		}
		else if (component->GetName() == "PowerConnection") {
			mPowerConnection1 = component;
		}
		else if (component->GetName() == "PowerConnection2") {
			mPowerConnection2 = component;
		}
	}
}

void APPBuildablePole::setPole2Location(FVector location) {
	mPowerPole2->AddRelativeLocation(location);
	mPowerConnection2->AddRelativeLocation(location);
	if (!location.IsZero()) {
		mPowerPole2->AddRelativeRotation(FRotator(0, 0, 180));
	}

	UpdateComponentTransforms();
	
}