#pragma once
#include "Core.h"
#include "Engine.h"

class USceneComponent : public UActorComponent 
{
public:
	FVector RelativeLocation;
	FVector RelativeRotation;
	FVector RelativeScale;

	FMatrix WorldMatrix;

	USceneComponent* Parent = nullptr;
	TArray<USceneComponent*> Children;

	FBoxSphereBounds* Bounds = nullptr;

public:
	USceneComponent();


	FVector GetRelativeLocation() const { return RelativeLocation; }
	FVector SetRelativeLocation(const FVector& NewLocation) {
		RelativeLocation = NewLocation;
		UpdateWorldMatrix();
	}

	FVector GetRelativeRotation() const { return RelativeRotation; }
	FVector SetRelativeRotation(const FVector& NewRotation) {
		RelativeRotation = NewRotation;
		UpdateWorldMatrix();
	}

	FVector GetRelativeScale() const { return RelativeScale; }
	FVector SetRelativeScale(const FVector& NewScale) {
		RelativeScale = NewScale;
		UpdateWorldMatrix();
	}

	FVector GetWorldLocation() const;
	FVector GetWorldScale() const;
	const FMatrix& GetWorldMatrix() const { return WorldMatrix; }

	// attachment
	void SetupAttachment(USceneComponent* NewParent);

	void UpdateWorldMatrix();

	// Bounds
	virtual void GetLocalBounds(FVector& OutMin, FVector& OutMax);

	void UpdateBounds();

	bool LineTrace(const FRay& Ray, float& OutDistance);
};