// ILikeBanas


#include "PPPowerPoleDoubleHologram.h"
#include "FGBuildableFoundation.h"
#include "FGBuildableWall.h"
#include "../PPBuildablePole.h"

#include "util/Logging.h"

APPPowerPoleDoubleHologram::APPPowerPoleDoubleHologram() : Super() {
}

void APPPowerPoleDoubleHologram::BeginPlay() {
	Super::BeginPlay();

	//SML::Logging::info(this->GetRootComponent()->GetNumChildrenComponents());
	TArray<USceneComponent*> components;
	this->GetRootComponent()->GetChildrenComponents(false, components);
	//SML::Logging::info(components.Num());
	for (auto component : components) {
		//SML::Logging::info(*component->GetName());
		if (component->GetName() == "PowerPole2") {
			powerPoleMesh2 = component;
		}
		else if (component->GetName() == "PowerConnection2") {
			powerConnection2 = component;
		}
	}
}

void APPPowerPoleDoubleHologram::CheckClearance() {
	Super::CheckClearance();
}

void APPPowerPoleDoubleHologram::SetHologramLocationAndRotation(const FHitResult& hitResult) {

	Super::SetHologramLocationAndRotation(hitResult);
	if (hitResult.IsValidBlockingHit() && hitResult.Actor != nullptr) {
		if (hitResult.Actor->IsA(AFGBuildableFoundation::StaticClass())) {

			AFGBuildableFoundation* foundation = Cast<AFGBuildableFoundation>(hitResult.Actor);
			
			if (foundation->mHeight == 100) {
				setComponentLocation(powerConnection2, FVector(-120, 0, 0));
				setComponentLocation(powerPoleMesh2, FVector(-40, 0, 0));
			}
			else if (foundation->mHeight == 200) {
				setComponentLocation(powerConnection2, FVector(-220, 0, 0));
				setComponentLocation(powerPoleMesh2, FVector(-140, 0, 0));
			}
			else if (foundation->mHeight == 400) {
				setComponentLocation(powerConnection2, FVector(-420, 0, 0));
				setComponentLocation(powerPoleMesh2, FVector(-340, 0, 0));
			}

			rotateComponent(powerConnection2, FRotator(90, 0, 0));
		}
	}


}

bool APPPowerPoleDoubleHologram::TrySnapToActor(const FHitResult& hitResult) {

	bool ret = Super::TrySnapToActor(hitResult);

	if (ret && hitResult.IsValidBlockingHit() && hitResult.Actor != nullptr) {
		if (hitResult.Actor->IsA(AFGBuildableWall::StaticClass())) {
			rotateComponent(powerConnection2, FRotator(0, 0, 0));
			setComponentLocation(powerConnection2, FVector(-80, 0, 0));
			setComponentLocation(powerPoleMesh2, FVector(0, 0, 0));
		}
	}

	return ret;
}

AActor* APPPowerPoleDoubleHologram::Construct(TArray< AActor* >& out_children, FNetConstructionID netConstructionID) {
	auto ret = Super::Construct(out_children, netConstructionID);
	
	if (ret->IsA(APPBuildablePole::StaticClass())) {
		auto buildable = Cast<APPBuildablePole>(ret);
		buildable->setPole2Location(newLocation);
		buildable->addLocation = newLocation;
	}

	return ret;
}