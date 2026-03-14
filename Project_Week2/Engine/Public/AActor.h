#pragma once
#include "Core.h"
#include "Engine.h"

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
	T* CreateDefaultSubobject(FString FName)
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

	void SetActorRotation(const FRotator& NewRot);
	FRotator GetActorRotation() const;

	USceneComponent* GetRootComponent() const { return RootComponent; }
	const Ftring& GetName() const { return ActorName; }

	TArray<UActorComponent*> OwnedComponents;
	FString ActorName;

	void RenderComponents(URenderer* Renderer)

	// 현재 액터가 활성화 상태인지 (Tick 실행 여부)
	bool bIsActive = true;
};