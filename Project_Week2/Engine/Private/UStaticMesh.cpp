#include "Engine.h"
#include <cmath>

UStaticMesh::UStaticMesh()
	: BoundsMin(-1.0f, -1.0f, -1.0f)
	, BoundsMax(1.0f, 1.0f, 1.0f)
{
}

void UStaticMesh::SetVertices(const TArray<FVertex>& InVertices)
{
	Vertices = InVertices;
}

void UStaticMesh::SetIndices(const TArray<uint32_t>& InIndices)
{
	Indices = InIndices;
}

void UStaticMesh::SetBounds(const FVector& InMin, const FVector& InMax)
{
	BoundsMin = InMin;
	BoundsMax = InMax;
}

void UStaticMesh::GetBounds(FVector& OutMin, FVector& OutMax) const
{
	OutMin = BoundsMin;
	OutMax = BoundsMax;
}

UStaticMesh* UStaticMesh::CreateCube()
{
	UStaticMesh* Mesh = new UStaticMesh();  // UFactory::CreateObject<UStaticMesh>();

	// Å¥ºê Á¤Á¡ µ¥ÀÌÅÍ (8°³ Á¤Á¡, °¢ ¸é¸¶´Ù »ö»ó)
	TArray<FVertex> Vertices = {
		// ¾Õ¸é (Z = 0.5)
		{-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f}, // 0: ÁÂÇÏ (»¡°­)
		{ 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f}, // 1: ¿ìÇÏ (ÃÊ·Ï)
		{ 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f}, // 2: ¿ì»ó (ÆÄ¶û)
		{-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f}, // 3: ÁÂ»ó (³ë¶û)

		// µÞ¸é (Z = -0.5)
		{-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f}, // 4: ÁÂÇÏ (¸¶Á¨Å¸)
		{ 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f}, // 5: ¿ìÇÏ (½Ã¾È)
		{ 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f}, // 6: ¿ì»ó (Èò»ö)
		{-0.5f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 1.0f}  // 7: ÁÂ»ó (È¸»ö)
	};

	// Å¥ºê ÀÎµ¦½º (12°³ »ï°¢Çü = 6°³ ¸é)
	TArray<uint32> Indices = {
		// ¾Õ¸é
		0, 1, 2,  2, 3, 0,
		// µÞ¸é
		4, 6, 5,  6, 4, 7,
		// ¿ÞÂÊ¸é
		4, 0, 3,  3, 7, 4,
		// ¿À¸¥ÂÊ¸é
		1, 5, 6,  6, 2, 1,
		// À§ÂÊ¸é
		3, 2, 6,  6, 7, 3,
		// ¾Æ·¡ÂÊ¸é
		4, 5, 1,  1, 0, 4
	};

	Mesh->SetVertices(Vertices);
	Mesh->SetIndices(Indices);
	Mesh->SetBounds(FVector(-0.5f, -0.5f, -0.5f), FVector(0.5f, 0.5f, 0.5f));

	return Mesh;
}