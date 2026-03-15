#pragma once
#include "Core.h"
#include "Engine.h"
#include "Renderer.h"

class UWorld : public UObject
{
public:
	UWorld();
	~UWorld();

	template<typename T>
	T* SpawnActor()
	{
		T* NewActor = new T(); // UFactory::CreateObject<T>();
		Actors.push_back(NewActor);
		// BeginPlay는 월드 초기화 시점에 한번에 호출
		return NewActor;
	}

	void Tick(float DeltaTime);

	void Render(URenderer* Renderer);

	bool LineTraceSingle(const FRay& Ray, FHitResult& OutHit);

	void Tick(float DeltaTime);
private:
	TArray<AActor*> Actors;
};