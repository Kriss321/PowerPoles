

#include "PPPowerPoleHologram.h"
#include "FGBuildableFoundation.h"
#include "FGBuildableWall.h"
#include "FGConstructDisqualifier.h"

#include "util/Logging.h"

APPPowerPoleHologram::APPPowerPoleHologram() : Super() {
	this->mValidHitClasses.Add(AFGBuildableFoundation::StaticClass());
	this->mValidHitClasses.Add(AFGBuildableWall::StaticClass());
	this->mMaxPlacementFloorAngle = 90;
	this->Foundation = false;
	this->newLocation = FVector(0, 0, 0);
}

void APPPowerPoleHologram::BeginPlay() {
	Super::BeginPlay();

	TArray<USceneComponent*> components;
	this->GetRootComponent()->GetChildrenComponents(false, components);
	for (auto component : components) {
		if (component->GetName() == "PowerPole") {
			powerPoleMesh = component;
		}
		else if (component->GetName() == "PowerConnection") {
			powerConnection = component;
		}
	}
}

void APPPowerPoleHologram::CheckValidFloor() {
	Super::CheckValidFloor();

	if (Foundation) {
		
		TArray<TSubclassOf<UFGConstructDisqualifier>> disqualifiers;
		this->GetConstructDisqualifiers(disqualifiers);
		this->ResetConstructDisqualifiers();
		for (auto disqualifier : disqualifiers) {
			if (disqualifier != UFGCDMustSnap::StaticClass()) {
				this->AddConstructDisqualifier(disqualifier);
			}
		}
	}
}

void APPPowerPoleHologram::CheckClearance() {
	Super::Super::CheckClearance();
}

void APPPowerPoleHologram::SetHologramLocationAndRotation(const FHitResult& hitResult) {
	if (hitResult.IsValidBlockingHit() && hitResult.Actor != nullptr) {
		if (hitResult.Actor->IsA(AFGBuildableFoundation::StaticClass())) {

			AFGBuildableFoundation* foundation = Cast<AFGBuildableFoundation>(hitResult.Actor);
			//this->CheckClearanceForPrimitive(foundation->GetClearanceComponent());
		}
	}
	if (hitResult.IsValidBlockingHit() && hitResult.Actor != nullptr) {
		this->Foundation = hitResult.Actor->IsA(AFGBuildableFoundation::StaticClass());
		
	}

	Super::SetHologramLocationAndRotation(hitResult);
	if (hitResult.IsValidBlockingHit() && hitResult.Actor != nullptr) {
		FVector location = this->GetActorLocation();
		FRotator rotation = this->GetActorRotation();
		if (hitResult.Actor->IsA(AFGBuildableFoundation::StaticClass())) {
			rotation.Yaw = hitResult.Actor->GetActorRotation().Yaw + (mScrollRotation * 9) % 360;

			if (abs(hitResult.ImpactPoint.Z) - abs(hitResult.Actor->GetActorLocation().Z) > 0) {
				rotation.Pitch = -90;
				location.Z += 30;
			}
			else {
				rotation.Pitch = 90;
				location.Z -= 30;
			}

			rotateComponent(powerConnection, FRotator(-90, 0, 0));
		}

		this->SetActorLocationAndRotation(location, rotation);
	}
}

bool APPPowerPoleHologram::TrySnapToActor(const FHitResult& hitResult) {

	bool ret = Super::TrySnapToActor(hitResult);

	if (ret) {
		rotateComponent(powerConnection, FRotator(0, 0, 0));
	}

	return ret;
}

void APPPowerPoleHologram::rotateComponent(USceneComponent* component, FRotator rotate) {
	if (component != nullptr) {
		auto powerConnectionRelativeTransform = component->GetRelativeTransform();
		auto powerConnectionRelativeTransformRotation = powerConnectionRelativeTransform.GetRotation().Rotator();
		powerConnectionRelativeTransformRotation = rotate;
		powerConnectionRelativeTransform.SetRotation(powerConnectionRelativeTransformRotation.Quaternion());
		component->SetRelativeTransform(powerConnectionRelativeTransform);
	}
}

void APPPowerPoleHologram::setComponentLocation(USceneComponent* component, FVector location) {
	if (component != nullptr) {
		auto powerConnectionRelativeTransform = component->GetRelativeTransform();
		auto powerConnectionRelativeTransformLocation = powerConnectionRelativeTransform.GetLocation();
		powerConnectionRelativeTransformLocation = location;
		powerConnectionRelativeTransform.SetLocation(powerConnectionRelativeTransformLocation);
		component->SetRelativeTransform(powerConnectionRelativeTransform);

		this->newLocation = location;
	}
}