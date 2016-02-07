#include "Vector3.h"
#include <cmath>

//Default Vector:  X = 0.0f   y = 0.0f   z = 0.0f
Vector3::Vector3()
{
	mX = 0.0f;
	mY = 0.0f;
	mZ = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;
}

void Vector3::SetX(float x)
{
	mX = x;
}

void Vector3::SetY(float y)
{
	mY = y;
}

void Vector3::SetZ(float z)
{
	mZ = z;
}

float Vector3::GetX()
{
	return mX;
}

float Vector3::GetY()
{
	return mY;
}

float Vector3::GetZ()
{
	return mZ;
}

//Returns the exact length of the vector, uses costly square root
float Vector3::Length()
{
	return std::sqrtf(mX * mX + mY * mY + mZ * mZ);
}

//Returns the length of the vector squared, basically same as length but without the costly square root
float Vector3::LengthSqrd()
{
	return mX * mX + mY * mY + mZ * mZ;
}

//Returns a normalized version of this vector
Vector3 Vector3::Normalize()
{
	float length = Length();

	//Avoid dividing by zero
	if (length > 0.0f)
	{
		return Vector3(mX / length, mY / length, mZ / length);
	}
	else
	{
		//Length is zero
		return Vector3();
	}
}

Vector3 Vector3::operator+(const Vector3& v) const
{
	return Vector3(mX + v.mX, mY + v.mY, mZ + v.mZ);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
	return Vector3(mX - v.mX, mY - v.mY, mZ - v.mZ);
}

//Scale
Vector3 Vector3::operator*(float scale) const
{
	return Vector3(scale * mX, scale * mY, scale * mZ);
}

//Scale
Vector3 operator*(float scale, const Vector3& v)
{
	return v * scale;
}

//Cross product 
Vector3 Vector3::operator^(const Vector3& v) const
{
	return Vector3(mY * v.mZ - mZ * v.mY,  //x
		mZ * v.mX - mX * v.mZ,  //y
		mX * v.mY - mY * v.mX); //z
}

//Dot product
float Vector3::operator*(const Vector3& v) const
{
	return mX * v.mX + mY * v.mY + mZ * v.mZ;
}
