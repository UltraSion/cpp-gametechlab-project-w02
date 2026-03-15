#pragma once
#include "Core.h"

class UActorComponent : public UObject
{
public:
	UActorComponent() : Owner(nullptr), bCanEverTick(true), bIsActivate(true) {}
	virtual ~UActorComponent() {}

	void SetOwner(class AActor* Inowner) { Owner = Inowner; }
	AActor* GetOwner() const { return Owner; }

	virtual void TickComponent(float DeltaTime) {} // 부품별 개별 로직 작성.
	virtual void BeginPlay(); // e.g. 큐브 컴포넌트가 렌더러에 넘겨줄 정점 데이터 계산, 다른 부품의 포인터 가져오기
	virtual void Activate(); 
	virtual void Deactivate();

	bool IsActive() const { return bIsActivate; }

public:
	bool bCanEverTick; // Tick을 켤지 끌지 결정
	AActor* Owner = nullptr; // 소유한 액터
	bool bIsActivate; // 현재 활성화 여부
	bool bHasBegunPlay = false; // BeginPlay가 호출되었는지 여부
};