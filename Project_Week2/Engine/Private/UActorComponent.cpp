#include "Engine.h"

void UActorComponent::BeginPlay()
{
	bHasBegunPlay = true;
}

void UActorComponent::Activate()
{
	bIsActivate = true;
}

void UActorComponent::Deactivate()
{
	bIsActivate = false;
}