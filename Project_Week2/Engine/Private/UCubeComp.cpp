#include "Engine.h"

UCubeComp::UCubeComp()
	: CubeSize(1.0f, 1.0f, 1.0f)
{
	PrimitiveType = EPrimitiveType::Cube;
	bVisible = false;
}

void UCubeComp::GetLocalBounds(FVector& OutMin, FVector& OutMax)
{
	FVector HalfSize = CubeSize * 0.5f;
	OutMin = FVector(-HalfSize.x, -HalfSize.y, -HalfSize.z);
	OutMax = FVector(HalfSize.x, HalfSize.y, HalfSize.z);
}

bool UCubeComp::LineTrace(const FRay& Ray, float& OutDistance)
{
	if (!Bounds) UpdateBounds();
	return Bounds->Intersect(Ray, OutDistance);;
}