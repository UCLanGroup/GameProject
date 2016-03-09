/**************************************************************************************************
	Module:       CVector3.h
	Author:       Laurent Noel
	Date created: 12/06/06

	Definition of the concrete class CVector3, three 32-bit floats representing a vector/point

	Copyright 2006, University of Central Lancashire and Laurent Noel

	Change history:
		V1.0    Created 12/06/06 - LN
**************************************************************************************************/

#ifndef TLX_C_VECTOR_3_H_INCLUDED
#define TLX_C_VECTOR_3_H_INCLUDED

#include "Defines.h"
#include "BaseMath.h"

namespace tlx
{

// Forward declaration of other classes used here (headers included in cpp)
class CQuaternion;


class CVector3
{
// Concrete class - public access
public:

	/*-----------------------------------------------------------------------------------------
		Constructors/Destructors
	-----------------------------------------------------------------------------------------*/

	// Default constructor - leaves values uninitialised
	CVector3() {}

	// Construct by value
	CVector3
	(
		const TFloat32 initX,
		const TFloat32 initY,
		const TFloat32 initZ
	) : x( initX ), y( initY ), z( initZ ) {}

	// Construct through pointer to three floats
	// Specifying explicit avoids defining an implicit conversion
	explicit CVector3
	(
		const TFloat32* pXYZ
	) : x( pXYZ[0] ), y( pXYZ[1] ), z( pXYZ[2] ) {}

	// Construct from a quaternion
	explicit CVector3
	(
		const CQuaternion& quat
	);


    // Copy constructor
    CVector3
	(
		const CVector3& src
	) : x( src.x ), y( src.y ), z( src.z ) {};

	// Assignment operator
    CVector3& operator=
	(
		const CVector3& src
	)
	{
		if ( this != &src )
		{
			x = src.x;
			y = src.y;
			z = src.z;
		}
		return *this;
	}

	// Destructor
	~CVector3() {}


	/*-----------------------------------------------------------------------------------------
		Setters
	-----------------------------------------------------------------------------------------*/

	// Set all three vector components
    void Set
	(
		const TFloat32 setX,
		const TFloat32 setY,
		const TFloat32 setZ
	)
	{
		x = setX;
		y = setY;
		z = setZ;
	}

	// Set the vector through a pointer to three floats
    void Set
	(
		const TFloat32* pXYZ
	)
	{
		x = pXYZ[0];
		y = pXYZ[1];
		z = pXYZ[2];
	}

	// Set the vector to (0,0,0)
    void SetZero()
	{
		x = y = z = 0.0f;
	}


	/*-----------------------------------------------------------------------------------------
		Array access
	-----------------------------------------------------------------------------------------*/

	// Access the x, y & z components in array style (e.g. v[1] same as v.y)
    TFloat32& operator[]
	(
		const TUInt32 index
	)
	{
		return (&x)[index];
	}

	// Access the x, y & z elements in array style - const result
	const TFloat32& operator[]
	(
		const TUInt32 index
	) const
	{
		return (&x)[index];
	}


	/*-----------------------------------------------------------------------------------------
		Comparisons
	-----------------------------------------------------------------------------------------*/
	// Equality operators defined as non-member operations after the class definition

	// Test if the vector is zero length (i.e. = (0,0,0))
	bool IsZero() const
	{
		return tlx::IsZero( x*x + y*y + z*z );
	}

	// Test if the vector is unit length (normalised)
	bool IsUnit() const
	{
		return tlx::IsZero( x*x + y*y + z*z - 1.0f );
	}


	/*-----------------------------------------------------------------------------------------
		Member Operators
	-----------------------------------------------------------------------------------------*/
	// Non-member versions defined after the class definition

	///////////////////////////////
	// Addition / subtraction

	// Add another vector to this vector
    CVector3& operator+=
	(
		const CVector3& vec
	)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	// Subtract another vector from this vector
    CVector3& operator-=
	(
		const CVector3& vec
	)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}


	////////////////////////////////////
	// Scalar multiplication & division

	// Multiply this vector by a scalar
	CVector3& operator*=
	(
		const TFloat32 scalar
	)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	// Divide this vector by a scalar
    CVector3& operator/=
	(
		const TFloat32 scalar
	)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}


	////////////////////////////////////
	// Other operations

	// Dot product of this with another vector
    TFloat32 Dot
	(
		const CVector3& vec
	) const
	{
	    return x*vec.x + y*vec.y + z*vec.z;
	}
	
	
	// Cross product of this with another vector
    CVector3 Cross
	(
		const CVector3& vec
	) const
	{
		return CVector3( y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x );
	}


	/*-----------------------------------------------------------------------------------------
		Length operations
	-----------------------------------------------------------------------------------------*/
	// Non-member versions defined after the class definition

	// Return length of this vector
	TFloat32 Length() const
	{
		return Sqrt( x*x + y*y + z*z );
	}

	// Return squared length of this vector
	// More efficient than Length when exact value is not required (e.g. for comparisons)
	TFloat32 LengthSquared() const
	{
		return x*x + y*y + z*z;
	}

	// Reduce vector to unit length
    void Normalise();


	/*-----------------------------------------------------------------------------------------
		Point related functions
	-----------------------------------------------------------------------------------------*/
	// Non-member versions defined after the class definition

	// Return distance from this point to another
    TFloat32 DistanceTo
	(
		const CVector3& pt
	);

	// Return squared distance from this point to another
	// More efficient than Distance when exact length is not required (e.g. for comparisons)
    TFloat32 DistanceToSquared
	(
		const CVector3& pt
	);


	/*---------------------------------------------------------------------------------------------
		Data
	---------------------------------------------------------------------------------------------*/
    
	// Standard vectors
	static const CVector3 kOrigin;
	static const CVector3 kXAxis;
	static const CVector3 kYAxis;
	static const CVector3 kZAxis;

    // Vector components
    TFloat32 x;
	TFloat32 y;
	TFloat32 z;
};


/*-----------------------------------------------------------------------------------------
	Non-member Operators
-----------------------------------------------------------------------------------------*/

///////////////////////////////
// Comparison

// Vector equality
inline bool operator==
(
	const CVector3& cmp1,
	const CVector3& cmp2
)
{
	return AreEqual( cmp1.x, cmp2.x ) && AreEqual( cmp1.y, cmp2.y ) && AreEqual( cmp1.z, cmp2.z );
}

// Vector inequality
inline bool operator!=
(
	const CVector3& cmp1,
	const CVector3& cmp2
)
{
	return !AreEqual( cmp1.x, cmp2.x ) || !AreEqual( cmp1.y, cmp2.y ) ||
		   !AreEqual( cmp1.z, cmp2.z );
}


///////////////////////////////
// Addition / subtraction

// Vector addition
inline CVector3 operator+
(
	const CVector3& vec1,
	const CVector3& vec2
)
{
	return CVector3( vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z );
}

// Vector subtraction
inline CVector3 operator-
(
	const CVector3& vec1,
	const CVector3& vec2
)
{
	return CVector3( vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z );
}

// Unary positive (for completeness)
inline CVector3 operator+
(
	const CVector3& vec
)
{
	return CVector3( vec );
}

// Unary negation
inline CVector3 operator-
(
	const CVector3& vec
)
{
	return CVector3( -vec.x, -vec.y, -vec.z );
}


////////////////////////////////////
// Scalar multiplication & division

// Vector multiplied by scalar
inline CVector3 operator*
(
	const CVector3& vec,
	const TFloat32  scalar
)
{
	return CVector3( vec.x * scalar, vec.y * scalar, vec.z * scalar );
}

// Scalar multiplied by vector
inline CVector3 operator*
(
	const TFloat32  scalar,
	const CVector3& vec
)
{
	return CVector3( vec.x * scalar, vec.y * scalar, vec.z * scalar );
}

// Vector divided by scalar
inline CVector3 operator/
(
	const CVector3& vec,
	const TFloat32  scalar
)
{
	return CVector3( vec.x / scalar, vec.y / scalar, vec.z / scalar );
}


////////////////////////////////////
// Other operations

// Dot product of two given vectors (order not important) - non-member version
inline TFloat32 Dot
(
	const CVector3& vec1,
	const CVector3& vec2
)
{
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

// Cross product of two given vectors (order is important) - non-member version
inline CVector3 Cross
(
	const CVector3& vec1,
	const CVector3& vec2
)
{
	return CVector3( vec1.y*vec2.z - vec1.z*vec2.y, vec1.z*vec2.x - vec1.x*vec2.z,
	                 vec1.x*vec2.y - vec1.y*vec2.x );
}


/*-----------------------------------------------------------------------------------------
	Non-member length operations
-----------------------------------------------------------------------------------------*/

// Return length of given vector - non-member version
inline TFloat32 Length
(
	const CVector3& vec
)
{
	return Sqrt( vec.x*vec.x + vec.y*vec.y + vec.z*vec.z );
}

// Return squared length of given vector - non-member version
// More efficient than Length when exact value is not required (e.g. for comparisons)
inline TFloat32 LengthSquared
(
	const CVector3& vec
)
{
	return vec.x*vec.x + vec.y*vec.y + vec.z*vec.z;
}

// Return a unit length version of the given vector - non-member version
CVector3 Normalise
(
	const CVector3& vec
);


/*-----------------------------------------------------------------------------------------
	Non-member point related functions
-----------------------------------------------------------------------------------------*/

// Return distance from one point to another - non-member version
TFloat32 Distance
(
	const CVector3& pt1,
	const CVector3& pt2
);

// Return squared distance from one point to another - non-member version
// More efficient than Distance when exact length is not required (e.g. for comparisons)
TFloat32 DistanceSquared
(
	const CVector3& pt1,
	const CVector3& pt2
);


} // namespace tlx

#endif // TLX_C_VECTOR_3_H_INCLUDED
