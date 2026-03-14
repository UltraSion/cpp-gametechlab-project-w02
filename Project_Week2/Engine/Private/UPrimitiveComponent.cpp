#include "UPrimitiveComponent.h"

UPrimitiveComponent::UPrimitiveComponent()
	: PrimitiveType(EPrimitiveType::Cube), bSelected(false), bVisible(true)
{
	WorldMatrix = FMatrix::Identity;
}

