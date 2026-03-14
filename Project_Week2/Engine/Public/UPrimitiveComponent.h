#pragma once

#include "Core.h"
#include "USceneComponent.h"

struct FBoxSphereBounds;

enum class EPrimitiveType : uint8 {
	Cube, Sphere, Triangle, Plane, StaticMesh
};

class UPrimitiveComponent : public USceneComponent
{
public:
	UPrimitiveComponent() {}
	virtual ~UPrimitiveComponent() {}

	EPrimitiveType PrimitiveType;
	bool bSelected = false;
	bool bVisible = true;

	virtual const char* GetTypeString() const = 0;
	virtual void Render() override = 0;
	virtual bool LineTrace(const struct FRay& Ray, float& OutDistance) override;
};