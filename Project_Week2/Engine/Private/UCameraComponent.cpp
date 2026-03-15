#include "Engine.h"

UCameraComponent::UCameraComponent()
	: FOV(90.0f)
	, AspectRatio(16.0f / 9.0f)
	, NearPlane(0.1f)
	, FarPlane(1000.0f)
{
	bCanEverTick = true;
	ViewMatrix = FMatrix::Identity;
	ProjectionMatrix = FMatrix::Identity;
}

void UCameraComponent::UpdateMatrices()
{
	// View Matrix 계산 (FMatrix의 정적 함수 사용)
	FVector CameraLocation = GetWorldLocation();
	FVector CameraRotation = RelativeRotation; // 라디안 단위

	ViewMatrix = FMatrix::MakeViewMatrix(CameraLocation, CameraRotation);

	// Projection Matrix 계산
	ProjectionMatrix = FMatrix::MakePerspectiveMatrix(FOV, AspectRatio, NearPlane, FarPlane);
}

void UCameraComponent::UpdateAspectRatio(uint32 Width, uint32 Height)
{
	if (Height > 0)
	{
		AspectRatio = static_cast<float>(Width) / static_cast<float>(Height);
		UpdateMatrices();
	}
}

FVector UCameraComponent::GetForwardVector() const
{
	// 월드 행렬에서 Forward 벡터 추출 (Z축, Row 2)
	FVector Forward(
		WorldMatrix.M[2][0],
		WorldMatrix.M[2][1],
		WorldMatrix.M[2][2]
	);
	return Forward.Normalize();
}

FVector UCameraComponent::GetRightVector() const
{
	// 월드 행렬에서 Right 벡터 추출 (X축, Row 0)
	FVector Right(
		WorldMatrix.M[0][0],
		WorldMatrix.M[0][1],
		WorldMatrix.M[0][2]
	);
	return Right.Normalize();
}

FVector UCameraComponent::GetUpVector() const
{
	// 월드 행렬에서 Up 벡터 추출 (Y축, Row 1)
	FVector Up(
		WorldMatrix.M[1][0],
		WorldMatrix.M[1][1],
		WorldMatrix.M[1][2]
	);
	return Up.Normalize();
}