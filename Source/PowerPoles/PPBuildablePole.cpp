// ILikeBanas


#include "PPBuildablePole.h"
#include "FGBuildableWire.h"

#include "util/Logging.h"

APPBuildablePole::APPBuildablePole() : Super() {
}

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
			mPowerConnection1 = Cast<UFGPowerConnectionComponent>(component);
		}
		else if (component->GetName() == "PowerConnection2") {
			mPowerConnection2 = Cast<UFGPowerConnectionComponent>(component);
		}
		else if (component->GetName() == "HiddenPowerConnection") {
			mHiddenPowerConnection = Cast<UFGPowerConnectionComponent>(component);
		}
	}
	if (mPowerConnection1 && mPowerConnection2 && mHiddenPowerConnection) {
		mPowerConnection1->AddHiddenConnection(mHiddenPowerConnection);
		mPowerConnection2->AddHiddenConnection(mHiddenPowerConnection);
	}
	
	if (!this->addLocation.IsZero()) {
		setPole2Location(this->addLocation);
	}
}

void APPBuildablePole::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void APPBuildablePole::setPole2Location(FVector location) {
	if (mPowerPole2 && mPowerConnection2) {
		mPowerPole2->AddRelativeLocation(location);
		mPowerConnection2->AddRelativeLocation(location);

		TArray<AFGBuildableWire*> wires;
		mPowerConnection2->GetWires(wires);
		for (auto wire : wires) {
			wire->Connect(wire->GetConnection(0), wire->GetConnection(1));
			wire->UpdateWireMesh();
			wire->UpdateComponentTransforms();
		}
		
		if (!location.IsZero()) {
			mPowerPole2->AddRelativeRotation(FRotator(0, 0, 180));
		}
		UpdateComponentTransforms();
	}
}