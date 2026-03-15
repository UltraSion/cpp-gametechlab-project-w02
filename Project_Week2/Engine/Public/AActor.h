#pragma once
#include "Core.h"
#include "Engine.h"
#include "Renderer.h"

class AActor : public UObject
{
public:

	AActor();
	virtual ~AActor() {}

	USceneComponent* RootComponent = nullptr;

	virtual void BeginPlay(); // 소유한 모든 컴포넌트의 BeginPlay 호출
	virtual void Tick(float DeltaTime);

	// 액터와 함께 파일에 저장됨. 기본형을 메모리에 하나 만들어둠 (CDO)
	template <typename T = UActorComponent >
	T* CreateDefaultSubobject(FString Name)
	{
		T* NewComp = UFactory::CreateObject<T>(Name);

		NewComp->SetOwner(this);
		OwnedComponents.push_back(NewComp);

		return NewComp;
	}
	
	// 런타임에 액터에 추가되는 컴포넌트. 휘발성
	template<typename T>
	T* AddComponent(const FString& Name)
	{
		T* NewComp = UFactory::CreateObject<T>(Name);

		NewComp->SetOwner(this);
		OwnedComponents.push_back(NewComp);

		return NewComp;
	}

	void SetActorLocation(const FVector& NewLoc);
	FVector GetActorLocation() const;

	void SetActorRotation(const FVector& NewRot);
	FVector GetActorRotation() const;

	void SetActorScale(const FVector& NewSca);
	FVector GetActorScale() const;

	USceneComponent* GetRootComponent() const { return RootComponent; }
	const FString& GetName() const { return ActorName; }

	void SetRootComponent(USceneComponent* NewRootComponent);
	void AttachComponentToRoot(USceneComponent* Component);



	TArray<UActorComponent*> OwnedComponents;
	FString ActorName;

	void RenderComponents(URenderer* Renderer);
	void RenderSceneComponentHierarchy(USceneComponent* SceneComp, URenderer* Renderer);


	// 현재 액터가 활성화 상태인지 (Tick 실행 여부)
	bool bIsActivate = true;
};