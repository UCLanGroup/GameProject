#pragma once

class Vector3
{
private:
	float mX;
	float mY;
	float mZ;

public:
	Vector3();
	Vector3(float x, float y, float z);

	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);

	float GetX();
	float GetY();
	float GetZ();

	float Length();
	float LengthSqrd();
	Vector3 Normalize();

	//Overloads
	Vector3 operator+(const Vector3& v) const;
	Vector3 operator-(const Vector3& v) const;
	Vector3 operator*(float scale) const;
	Vector3 operator^(const Vector3& v) const;	//Cross Product
	float operator*(const Vector3& v) const;	//Dot Product
	friend Vector3 operator*(float scale, const Vector3& v);
};

