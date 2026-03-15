#include "Math/FMatrix.h"
#include <cmath>

const FMatrix FMatrix::Identity = FMatrix::MakeIdentity();

FMatrix::FMatrix()
{
	for (int Row = 0; Row < 4; Row++)
	{
		for (int Col = 0; Col < 4; Col++)
		{
			M[Row][Col] = 0.0f;
		}
	}
}

FMatrix FMatrix::MakeIdentity()
{
	FMatrix Result;

	Result.M[0][0] = 1.0f;
	Result.M[1][1] = 1.0f;
	Result.M[2][2] = 1.0f;
	Result.M[3][3] = 1.0f;

	return Result;
}

FMatrix FMatrix::MakeTranslation(const FVector& Translation)
{
	FMatrix Result = FMatrix::MakeIdentity();

	Result.M[3][0] = Translation.x;
	Result.M[3][1] = Translation.y;
	Result.M[3][2] = Translation.z;

	return Result;
}

FMatrix FMatrix::MakeScale(const FVector& Scale)
{
	FMatrix Result = FMatrix::MakeIdentity();

	Result.M[0][0] = Scale.x;
	Result.M[1][1] = Scale.y;
	Result.M[2][2] = Scale.z;

	return Result;
}

FMatrix FMatrix::MakeRotationX(float Radians)
{
	FMatrix Result = FMatrix::MakeIdentity();

	const float C = cosf(Radians);
	const float S = sinf(Radians);

	Result.M[1][1] = C;
	Result.M[1][2] = S;
	Result.M[2][1] = -S;
	Result.M[2][2] = C;

	return Result;
}

FMatrix FMatrix::MakeRotationY(float Radians)
{
	FMatrix Result = FMatrix::MakeIdentity();

	const float C = cosf(Radians);
	const float S = sinf(Radians);

	Result.M[0][0] = C;
	Result.M[0][2] = -S;
	Result.M[2][0] = S;
	Result.M[2][2] = C;

	return Result;
}

FMatrix FMatrix::MakeRotationZ(float Radians)
{
	FMatrix Result = FMatrix::MakeIdentity();

	const float C = cosf(Radians);
	const float S = sinf(Radians);

	Result.M[0][0] = C;
	Result.M[0][1] = S;
	Result.M[1][0] = -S;
	Result.M[1][1] = C;

	return Result;
}

FMatrix FMatrix::MakeRotationXYZ(const FVector& RadiansXYZ)
{
	FMatrix RX = MakeRotationX(RadiansXYZ.x);
	FMatrix RY = MakeRotationY(RadiansXYZ.y);
	FMatrix RZ = MakeRotationZ(RadiansXYZ.z);

	return RX * RY * RZ;
}

FMatrix FMatrix::MakeViewMatrix(const FVector& CameraLocation, const FVector& CameraRotation)
{
	FMatrix InvTranslation = MakeTranslation(FVector(-CameraLocation.x, -CameraLocation.y, -CameraLocation.z));

	FMatrix InvRotZ = MakeRotationZ(-CameraRotation.z);
	FMatrix InvRotY = MakeRotationY(-CameraRotation.y);
	FMatrix InvRotX = MakeRotationX(-CameraRotation.x);

	return InvTranslation * InvRotZ * InvRotY * InvRotX;
}

FMatrix FMatrix::MakePerspectiveMatrix(float FOVDegrees, float AspectRatio, float NearClip, float FarClip)
{
	const float FOVRadians = FOVDegrees * 3.14159265358979323846f / 180.0f;
	const float YScale = 1.0f / std::tan(FOVRadians * 0.5f);
	const float XScale = YScale / AspectRatio;

	FMatrix Mat = {};

	Mat.M[0][0] = XScale;
	Mat.M[0][1] = 0.0f;
	Mat.M[0][2] = 0.0f;
	Mat.M[0][3] = 0.0f;

	Mat.M[1][0] = 0.0f;
	Mat.M[1][1] = YScale;
	Mat.M[1][2] = 0.0f;
	Mat.M[1][3] = 0.0f;

	Mat.M[2][0] = 0.0f;
	Mat.M[2][1] = 0.0f;
	Mat.M[2][2] = FarClip / (FarClip - NearClip);
	Mat.M[2][3] = 1.0f;

	Mat.M[3][0] = 0.0f;
	Mat.M[3][1] = 0.0f;
	Mat.M[3][2] = (-NearClip * FarClip) / (FarClip - NearClip);
	Mat.M[3][3] = 0.0f;

	return Mat;
}


FMatrix FMatrix::operator*(const FMatrix& Rhs) const
{
	FMatrix Result;

	for (int Row = 0; Row < 4; Row++)
	{
		for (int Col = 0; Col < 4; Col++)
		{
			Result.M[Row][Col] =
				M[Row][0] * Rhs.M[0][Col] +
				M[Row][1] * Rhs.M[1][Col] +
				M[Row][2] * Rhs.M[2][Col] +
				M[Row][3] * Rhs.M[3][Col];
		}
	}

	return Result;
}

FVector4 FMatrix::operator*(const FVector4& Vec) const
{
	return FVector4(
		M[0][0] * Vec.x + M[1][0] * Vec.y + M[2][0] * Vec.z + M[3][0] * Vec.w,
		M[0][1] * Vec.x + M[1][1] * Vec.y + M[2][1] * Vec.z + M[3][1] * Vec.w,
		M[0][2] * Vec.x + M[1][2] * Vec.y + M[2][2] * Vec.z + M[3][2] * Vec.w,
		M[0][3] * Vec.x + M[1][3] * Vec.y + M[2][3] * Vec.z + M[3][3] * Vec.w
	);
}

FMatrix FMatrix::Transpose(const FMatrix& Mat)
{
	FMatrix Result;

	for (int Row = 0; Row < 4; ++Row)
	{
		for (int Col = 0; Col < 4; ++Col)
		{
			Result.M[Row][Col] = Mat.M[Col][Row];
		}
	}

	return Result;
}