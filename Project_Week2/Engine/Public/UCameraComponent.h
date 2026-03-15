#pragma once
#include "Core.h"
#include "USceneComponent.h"

class UCameraComponent : public USceneComponent
{
public:
	UCameraComponent();

	void UpdateMatrices();

	FMatrix GetViewMatrix() const { return ViewMatrix; }
	FMatrix GetProjectionMatrix() const { return ProjectionMatrix; }

	void UpdateAspectRatio(uint32 Width, uint32 Height);

	// 유틸리티 함수들
	FVector GetForwardVector() const;
	FVector GetUpVector() const;

public:
	float FOV; // Field of View 카메라 시야각
	float AspectRatio;
	float NearPlane;
	float FarPlane;

private:
	FMatrix ViewMatrix;
	FMatrix ProjectionMatrix;
};