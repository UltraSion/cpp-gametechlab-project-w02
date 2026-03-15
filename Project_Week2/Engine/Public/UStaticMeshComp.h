#pragma once
#include "Core.h"
#include "UPrimitiveComponent.h"

class UStaticMesh; // 전방 선언

class UStaticMeshComp : public UPrimitiveComponent
{
public:
	UStaticMeshComp();
	virtual ~UStaticMeshComp();

	virtual const char* GetTypeString() const override
	{
		return "StaticMesh";
	}

	virtual void Render(URenderer* Renderer) override;
	virtual void BeginPlay() override;
	virtual void GetLocalBounds(FVector& OutMin, FVector& OutMax) override;

	// 스태틱 메시 설정
	void SetStaticMesh(UStaticMesh* NewMesh);
	UStaticMesh* GetStaticMesh() const { return StaticMesh; }

private:
	UStaticMesh* StaticMesh = nullptr;
	ID3D11Buffer* VertexBuffer = nullptr;
	ID3D11Buffer* IndexBuffer = nullptr;
	UINT IndexCount = 0;

	void CreateRenderResources(URenderer* Renderer);
	void ReleaseRenderResources();
};