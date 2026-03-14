#pragma once
#include "Core.h"

class UWorld
{
public:
	UWorld();
	~UWorld();

	template<typename T>
	T* SpawnActor();
	{
		T* NewActor = new T();
		Actors.push_back(NewActor);
		// BeginPlay는 월드 초기화 시점에 한번에 호출
		return NewActor;
	}

	void Tick(float DeltaTime);

	void Render();

	void LineTraceSingle(const FRay& Ray, FHitResult& OutHit);
private:
	TArray<AActor*> Actors;
};