#pragma once
#include "Core.h"
#include "Engine.h"

class UCameraComponent : public USceneComponent
{
public:
	UCameraComponent();
	virtual ~UCameraComponent() {}

	// 카메라 행렬 업데이트
	void UpdateMatrices();

	// Getter
	FMatrix GetViewMatrix() const { return ViewMatrix; }
	FMatrix GetProjectionMatrix() const { return ProjectionMatrix; }

	// 화면 비율 업데이트
	void UpdateAspectRatio(uint32 Width, uint32 Height);

	// 유틸리티 함수들
	FVector GetForwardVector() const;
	FVector GetRightVector() const;
	FVector GetUpVector() const;

public:
	float FOV = 90.0f;              // Field of View (도 단위)
	float AspectRatio = 16.0f / 9.0f;
	float NearPlane = 0.1f;
	float FarPlane = 1000.0f;

private:
	FMatrix ViewMatrix;
	FMatrix ProjectionMatrix;
};