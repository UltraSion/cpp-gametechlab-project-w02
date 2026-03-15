#pragma once
#include "Core.h"

// 정점, 인덱스 데이터 저장
class UStaticMesh : public UObject
{
public:
	UStaticMesh();
	virtual ~UStaticMesh() {}

	void SetVertices(const TArray<FVertex>& InVertices);
	const TArray<FVertex>& GetVertices() const { return Vertices; }

	void SetIndices(const TArray<uint32_t>& InIndices);
	const TArray<uint32>& GetIndices() const { return Indices; }

	void SetBounds(const FVector& InMin, const FVector& InMax);
	void GetBounds(FVector& OutMin, FVector& OutMax) const;

	static UStaticMesh* CreateCube();
	//static UStaticMesh* CreateSphere(int Segments = 16);

private:
	TArray<FVertex> Vertices;
	TArray<uint32_t> Indices;
	FVector BoundsMin;
	FVector BoundsMax;
};