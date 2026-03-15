#include "Core.h"
#include "Engine.h"

AActor::AActor()
	: bIsActivate(true)
	, ActorName("Defaul")
	, RootComponent(nullptr)
{

}

void AActor::Tick(float DeltaTime)
{
	if (!bIsActivate) return;

	for (UActorComponent* Comp : OwnedComponents)
	{
		if (Comp && Comp->bCanEverTick && Comp->IsActive())
		{
			Comp->TickComponent(DeltaTime);
		}
	}
}

void AActor::BeginPlay()
{
	if (!bIsActivate) return;

	for (UActorComponent* Comp : OwnedComponents)
	{
		if (Comp && !Comp->bHasBegunPlay)
		{
			Comp->BeginPlay();
		}
	}
}

FVector AActor::GetActorLocation() const
{
	return RootComponent ? RootComponent->GetRelativeLocation() : FVector(0, 0, 0);
}

void AActor::SetActorLocation(const FVector& NewLoc)
{
	if (RootComponent)
	{
		RootComponent->SetRelativeLocation(NewLoc);
	}
}

void AActor::SetActorRotation(const FVector& NewRot)
{
	if (RootComponent)
	{
		RootComponent->SetRelativeRotation(NewRot);
	}
}

FVector AActor::GetActorRotation() const
{
	return RootComponent ? RootComponent->GetRelativeRotation() : FVector(0, 0, 0);
}

void AActor::SetActorScale(const FVector& NewRot)
{
	if (RootComponent)
	{
		RootComponent->SetRelativeScale(NewRot);
	}
}

FVector AActor::GetActorScale() const
{
	return RootComponent ? RootComponent->GetRelativeScale() : FVector(0, 0, 0);
}


void AActor::SetRootComponent(USceneComponent* NewRootComponent)
{
	RootComponent = NewRootComponent;
	if (RootComponent)
	{
		RootComponent->SetOwner(this);
	}
}

void AActor::AttachComponentToRoot(USceneComponent* Component)
{
	if (Component && RootComponent)
	{
		Component->SetupAttachment(RootComponent);
		Component->SetOwner(this);
	}
}

void AActor::RenderComponents(URenderer* Renderer)
{
	// RootComponent부터 계층적으로 렌더링
	if (RootComponent)
	{
		RenderSceneComponentHierarchy(RootComponent, Renderer);
	}
}

void AActor::RenderSceneComponentHierarchy(USceneComponent* SceneComp, URenderer* Renderer)
{
	if (!SceneComp) return;

	// 현재 컴포넌트가 렌더링 가능한지 확인
	UPrimitiveComponent* Primitive = dynamic_cast<UPrimitiveComponent*>(SceneComp);
	if (Primitive && Primitive->bVisible)
	{
		Primitive->Render(Renderer);
	}

	// 자식 컴포넌트들도 재귀적으로 렌더링
	for (USceneComponent* Child : SceneComp->Children)
	{
		RenderSceneComponentHierarchy(Child, Renderer);
	}
}