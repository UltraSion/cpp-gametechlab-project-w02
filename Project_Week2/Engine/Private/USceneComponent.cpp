#include "USceneComponent.h"

USceneComponent::USceneComponent()
	: RelativeLocation(0, 0, 0), RelativeRotation(0, 0, 0), RelativeScale(1, 1, 1), Parent(nullptr) {
	WorldMatrix = FMatrix::Identity;
}

void USceneComponent::SetupAttachment(USceneComponent* NewParent)
{
	if (NewParent)
	{
		Parent = NewParent;
		Parent->Children.push_back(this);
		UpdateWorldMatrix();
	}
}

void USceneComponent::UpdateWorldMatrix()
{
	// S * R * T
	FMatrix S = FMatrix::Scale(RelativeScale);
	FMatrix R = FMatrix::Rotation(RelativeRotation);
	FMatrix T = FMatrix::Translation(RelativeLocation);

	FMatrix LocalMatrix = S * R * T;

	if (Parent)
	{
		WorldMatrix = LocalMatrix * Parent->GetWorldMatrix();
	}
	else
	{
		WorldMatrix = LocalMatrix;
	}

	for (auto* Child : Children)
	{
		if (Child) Child->UpdateWorldMatrix();
	}

	UpdateBounds();
}

FVector USceneComponent::GetWorldLocation() const
{
	// 월드 매트릭스에서 위치 추출
	/*return WorldMatrix.GetTranslation();*/
	return FVector(WorldMatrix.m[3][0], WorldMatrix.m[3][1], WorldMatrix.m[3][2]);
}

virtual void GetLocalBounds(FVector& OutMin, FVector& OutMax)
{
	OutMin = FVector(0, 0, 0);
	OutMax = FVector(0, 0, 0);
}

void UpdateBounds()
{
	FVector LocalMin, LocalMax;
	GetLocalBounds(LocalMin, LocalMax);
	
	// 월드 행렬에서 위치(Origin) 추출
	Bounds.Origin = FVector(WorldMatrix._41, WorldMatrix._42, WorldMatrix._43);

	// 로컬 크기에 월드 스케일을 적용하여 월드 크기(Extent) 계산
	FVector Scale = GetWorldScale();
	Bounds.BoxExtent = ((LocalMax - LocalMin) * 0.5f) * Scale;

	// 구체 반지름 업데이트
	Bounds.SphereRadius = Bounds.BoxExtent.Length();
}

virtual bool LineTrace(const FRay& Ray, float& OutDistance)
{
	if (!bVisible) return false;

	return Bounds.Intersect(Ray, OutDistance);
}