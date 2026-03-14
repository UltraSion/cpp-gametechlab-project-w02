#include "AActor.h"
#include "UActorComponent.h"
#include "USceneComponent.h"

AActor::AActor()
	: bIsActive(true)
	, ActorName("Defaul")
{

}

void AActor::BeginPlay()
{
	if (!bIsActive) return;

	for (UActorComponent* Comp : OwnedComponents)
	{
		if (Comp && !Comp->bHasBegunPlay)
		{
			Comp->BeginPlay();
		}
	}
}

void AActor::GetActorLocation() const
{
	return RootComponent ? RootComponent->GetLocation() : FVector(0, 0, 0);
}

void AActor::SetActorLocation(const FVector& NewLoc)
{
	if (RootComponent)
	{
		RootComponent->SetRelativeLocation(NewLoc);
	}
}

void AActor::RenderComponents(URenderer* Renderer)
{
	for (UComponent* Comp : OwnedComponents)
	{
		// 그릴 수 있는 컴포넌트인지 확인
		UPrimitiveComponent* Primitive = dynamic_cast<UPrimitiveComponent*>(Comp);

		if (Primitive && Primitive->bVisible)
		{
			Primitive->Render(Renderer); // 컴포넌트 자신의 Render() 호출. 큐브면 큐브정점, 기즈모면 화살표 정점 보냄
		}
	}
}