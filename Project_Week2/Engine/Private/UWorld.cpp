#include "UWorld.h"
#include "AActor.h"
#include "UPrimitiveComponent.h"

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
		if (Actor && Actor->bIsActive)
		{
			Actor->Tick(DeltaTime);
		}
	}
}

void UWorld::Render()
{
	for (AActor* Actor : Actors)
	{
		Actor->RenderComponents();
	}
}

void UWorld::LineTraceSingle(const FRay& Ray, FHitResult& OutHit) {
	float ClosestDistance = FLT_MAX;
	bool bFound = false;

	for (AActor* Actor : Actors) {
		for (USceneComponent* SceneComp : Actor->OwnedComponents) {
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

	return bFound;
}