#include "UActorComponent.h"

void UActorComponent::BeginPlay()
{
	bHasBegunPlay = true;
}

void UActorComponent::Activate()
{
	bIsActive = true;
}

void UActorComponent::Deactivate()
{
	bIsActive = false;
}