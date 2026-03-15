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
	FMatrix S = FMatrix::MakeScale(RelativeScale);
	FMatrix R = FMatrix::MakeRotationXYZ(RelativeRotation);
	FMatrix T = FMatrix::MakeTranslation(RelativeLocation);

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
	return FVector(WorldMatrix.M[3][0], WorldMatrix.M[3][1], WorldMatrix.M[3][2]);
}

void GetLocalBounds(FVector& OutMin, FVector& OutMax)
{
	OutMin = FVector(0, 0, 0);
	OutMax = FVector(0, 0, 0);
}

FVector USceneComponent::GetWorldScale() const
{
	// 월드 매트릭스에서 스케일 추출
	float ScaleX = FVector(WorldMatrix.M[0][0], WorldMatrix.M[0][1], WorldMatrix.M[0][2]).Length();
	float ScaleY = FVector(WorldMatrix.M[1][0], WorldMatrix.M[1][1], WorldMatrix.M[1][2]).Length();
	float ScaleZ = FVector(WorldMatrix.M[2][0], WorldMatrix.M[2][1], WorldMatrix.M[2][2]).Length();
	return FVector(ScaleX, ScaleY, ScaleZ);
}

void USceneComponent::UpdateBounds()
{
	if (!Bounds)
	{
		Bounds = new FBoxSphereBounds();
	}

	FVector LocalMin, LocalMax;
	GetLocalBounds(LocalMin, LocalMax);

	// 월드 행렬에서 위치(Origin) 추출
	Bounds->Origin = GetWorldLocation();

	// 로컬 크기에 월드 스케일을 적용하여 월드 크기(Extent) 계산
	FVector Scale = GetWorldScale();
	Bounds->BoxExtent = ((LocalMax - LocalMin) * 0.5f) * Scale;

	// 구체 반지름 업데이트
	Bounds->SphereRadius = Bounds->BoxExtent.Length();
}


bool LineTrace(const FRay& Ray, float& OutDistance)
{
	if (!Bounds) return false;

	return Bounds.Intersect(Ray, OutDistance);
}