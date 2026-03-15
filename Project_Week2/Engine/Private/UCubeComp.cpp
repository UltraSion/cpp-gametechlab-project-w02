#include "UCubeComp.h"
#include "URenderer.h"

UCubeComp::UCubeComp()
{
	PrimitiveType = EPrimitiveType::Cube;
	bVisible = true;

	// 큐브 정점 데이터 생성
	GenerateCubeVertices();
}

void UCubeComp::GenerateCubeVertices()
{
	// 큐브의 8개 정점 정의 (단위 큐브: -0.5 ~ 0.5)
	CubeVertices = {
		// 앞면 (Z = 0.5)
		FVertex{-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f}, // 좌하
		FVertex{ 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f}, // 우하
		FVertex{ 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f}, // 우상
		FVertex{-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f}, // 좌상

		// 뒷면 (Z = -0.5)
		FVertex{-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f},
		FVertex{ 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f},
		FVertex{ 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f},
		FVertex{-0.5f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 1.0f}
	};

	// 큐브의 인덱스 (삼각형 12개)
	CubeIndices = {
		// 앞면
		0, 1, 2,  2, 3, 0,
		// 뒷면  
		4, 6, 5,  6, 4, 7,
		// 왼쪽면
		4, 0, 3,  3, 7, 4,
		// 오른쪽면
		1, 5, 6,  6, 2, 1,
		// 위쪽면
		3, 2, 6,  6, 7, 3,
		// 아래쪽면
		4, 5, 1,  1, 0, 4
	};
}

void UCubeComp::Render(URenderer* Renderer)
{
	if (!bVisible || !Renderer) return;

	// 월드 변환 행렬을 렌더러에 전달
	Renderer->UpdateConstantMTX(GetWorldMatrix());

	// 정점 버퍼 생성 및 렌더링
	// 실제 구현은 렌더러의 구조에 따라 달라질 수 있음
	if (!VertexBuffer)
	{
		CreateVertexBuffer(Renderer);
	}

	Renderer->RenderPrimitive(VertexBuffer, CubeIndices.size());
}

void UCubeComp::CreateVertexBuffer(URenderer* Renderer)
{
	// Direct3D 정점 버퍼 생성 로직
	// 실제 구현은 렌더러 구조에 맞게 조정 필요
}

void UCubeComp::BeginPlay()
{
	UPrimitiveComponent::BeginPlay();

	// 큐브 전용 초기화 로직
	UpdateBounds();
}