#include "UStaticMeshComp.h"
#include "URenderer.h"

UStaticMeshComp::UStaticMeshComp()
{
	PrimitiveType = EPrimitiveType::StaticMesh;
	bVisible = true;
}

UStaticMeshComp::~UStaticMeshComp()
{
	ReleaseRenderResources();
}

void UStaticMeshComp::SetStaticMesh(UStaticMesh* NewMesh)
{
	if (StaticMesh != NewMesh)
	{
		StaticMesh = NewMesh;

		// 렌더 리소스 재생성
		ReleaseRenderResources();
		if (StaticMesh)
		{
			// 새로운 메시에 대한 렌더 리소스 생성은 다음 Render 호출 시 수행
		}

		UpdateBounds();
	}
}

void UStaticMeshComp::Render(URenderer* Renderer)
{
	if (!bVisible || !Renderer || !StaticMesh) return;

	// 렌더 리소스가 없으면 생성
	if (!VertexBuffer)
	{
		CreateRenderResources(Renderer);
	}

	// 월드 변환 행렬을 렌더러에 전달
	Renderer->UpdateConstantMTX(GetWorldMatrix());

	// 메시 렌더링
	if (VertexBuffer && IndexBuffer)
	{
		Renderer->RenderPrimitive(VertexBuffer, IndexCount);
	}
}

void UStaticMeshComp::BeginPlay()
{
	UPrimitiveComponent::BeginPlay();

	// 스태틱 메시 컴포넌트 초기화
	if (StaticMesh)
	{
		UpdateBounds();
	}
}

void UStaticMeshComp::GetLocalBounds(FVector& OutMin, FVector& OutMax)
{
	if (StaticMesh)
	{
		// 스태틱 메시로부터 바운딩 박스 정보 가져오기
		// StaticMesh->GetBounds(OutMin, OutMax);

		// 임시로 기본 크기 설정
		OutMin = FVector(-1.0f, -1.0f, -1.0f);
		OutMax = FVector(1.0f, 1.0f, 1.0f);
	}
	else
	{
		OutMin = OutMax = FVector(0, 0, 0);
	}
}

void UStaticMeshComp::CreateRenderResources(URenderer* Renderer)
{
	if (!StaticMesh || !Renderer) return;

	// 스태틱 메시로부터 정점 데이터와 인덱스 데이터를 가져와서
	// Direct3D 버퍼를 생성하는 로직
	// 실제 구현은 UStaticMesh 클래스 구조에 따라 달라짐
}

void UStaticMeshComp::ReleaseRenderResources()
{
	if (VertexBuffer)
	{
		VertexBuffer->Release();
		VertexBuffer = nullptr;
	}

	if (IndexBuffer)
	{
		IndexBuffer->Release();
		IndexBuffer = nullptr;
	}
}