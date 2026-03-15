#pragma once
#include "Engine.h"

class UCubeComp : public UPrimitiveComponent
{
public:
	UCubeComp();
	virtual ~UCubeComp() {}

	virtual const char* GetTypeString() const override
	{
		return "Cube";
	}

	virtual void GetLocalBounds(FVector& OutMin, FVector& OutMax) override
	{
		OutMin = FVector(-0.5f, -0.5f, -0.5f);
		OutMax = FVector(0.5f, 0.5f, 0.5f);
	}

	void SetCuveSize(const FVector& Size) {
		CubeSize = Size;
	}
	FVector GetCubeSize() const {
		return CubeSize;
	}

private:
	FVector CubeSize = FVector(1.0f, 1.0f, 1.0f);
};