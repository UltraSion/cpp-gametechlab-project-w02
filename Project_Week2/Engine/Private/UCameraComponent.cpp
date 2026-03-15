#include "UCameraComponent.h"

UCameraComponent::UCameraComponent()
	: FOV(90.0f)
	, AspectRatio(16.0f / 9.0f)
	, NearPlane(0.1f)
	, FarPlane(1000.0f)
{
	// 초기 행렬 설정
	UpdateMatrices();
}

void UCameraComponent::UpdateMatrices()
{
	// View Matrix 계산 (카메라 위치와 회전에 따라)
	FVector CameraLocation = GetWorldLocation();
	FVector Forward = GetForwardVector();  // 카메라가 바라보는 방향
	FVector Up = GetUpVector();           // 카메라의 위쪽 방향

	// Look-At 행렬 생성 (간단한 구현)
	ViewMatrix = FMatrix::LookAt(CameraLocation, CameraLocation + Forward, Up);

	// Projection Matrix 계산
	float FovRadians = FOV * (3.14159f / 180.0f); // 도를 라디안으로 변환
	ProjectionMatrix = FMatrix::Perspective(FovRadians, AspectRatio, NearPlane, FarPlane);
}

void UCameraComponent::UpdateAspectRatio(uint32 Width, uint32 Height)
{
	if (Height > 0)
	{
		AspectRatio = (float)Width / (float)Height;
		UpdateMatrices(); // 비율 변경 시 투영 행렬 업데이트
	}
}

// 추가 유틸리티 함수들
FVector UCameraComponent::GetForwardVector() const
{
	// 회전에서 앞쪽 벡터 계산 (간단한 구현)
	FVector Rotation = GetRelativeRotation();
	// 실제로는 회전 행렬에서 Forward 벡터를 추출해야 함
	return FVector(1.0f, 0.0f, 0.0f); // 임시로 X축 방향
}

FVector UCameraComponent::GetUpVector() const
{
	// 회전에서 위쪽 벡터 계산 (간단한 구현)
	return FVector(0.0f, 0.0f, 1.0f); // 임시로 Z축 방향
}