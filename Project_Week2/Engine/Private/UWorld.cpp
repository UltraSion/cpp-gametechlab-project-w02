#include "Engine.h"
#include "URenderer.h"

UWorld::UWorld() {}

UWorld::~UWorld()
{
	for (AActor* Actor : Actors)
	{
		delete Actor;
	}
	Actors.clear();
}

void UWorld::Tick(float DeltaTime)
{
	for (AActor* Actor : Actors)
	{
		if (Actor && Actor->bIsActivate)
		{
			Actor->Tick(DeltaTime);
		}
	}
}

void UWorld::Render(URenderer* Renderer)
{
	for (AActor* Actor : Actors)
	{
		Actor->RenderComponents(Renderer);
	}
}

bool UWorld::LineTraceSingle(const FRay& Ray, FHitResult& OutHit) { // 레이와 충돌한 결과 정보를 담는 구조체
	float ClosestDistance = FLT_MAX;
	bool bFound = false;

	for (AActor* Actor : Actors) {
		for (UActorComponent* Comp : Actor->OwnedComponents) {
			USceneComponent* SceneComp = dynamic_cast<USceneComponent*>(Comp);
			if (SceneComp) {
				float CurrentDist = 0.0f;

				// 각 컴포넌트에게 물어봄. SceneComponent의 LineTrace가 Bounds.Intersect 호출
				if (SceneComp->LineTrace(Ray, CurrentDist)) {
					if (CurrentDist < ClosestDistance) {
						ClosestDistance = CurrentDist;
						OutHit.Actor = Actor;
						OutHit.Component = SceneComp;
						OutHit.Distance = CurrentDist;
						bFound = true;
					}
				}
			}
		}
	}

	return bFound;
}