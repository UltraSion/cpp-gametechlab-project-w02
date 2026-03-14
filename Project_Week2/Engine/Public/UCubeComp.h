#pragma once
#include "UObject.h"
#include "UPrimitiveComponent.h"

class UCubeComp : public UPrimitiveComponent
{
public:
	UCubeComp();
	virtual ~UCubeComp() {}

	virtual const char* GetTypeString() const override
	{
		return "Cube";
	}

	virtual void Render() override;

	virtual void GetLocalBounds(FVector& OutMin, FVector& OutMax) override
	{
		OutMin = FVector(-0.5f, -0.5f, -0.5f);
		OutMax = FVector(0.5f, 0.5f, 0.5f);
	}

private:
	void GenerateCubeVertices();
};