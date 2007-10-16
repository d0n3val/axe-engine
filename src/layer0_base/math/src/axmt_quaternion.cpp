/**
* @file
* axe_matrix_4x4 class code without optimizations (only FU here)
*/
#include "axmt_stdafx.h"

// -----------------------------------------------------------------

/**
* We omit constructors for performance ... this method will be our
* customized constructors
*/
axe_quaternion &axe_quaternion::create( const float& _w, const float& _x, const float& _y, const float& _z )
{
  w = _w;
  x = _x;
  y = _y;
  z = _z;
  return( *this );
}

axe_quaternion &axe_quaternion::create( const axe_quaternion& q )
{
  w = q.w;
  x = q.x;
  y = q.y;
  z = q.z;
  return( *this );
}

// -----------------------------------------------------------------
// Cast operators --------------------------------------------------
axe_quaternion::operator axe_euler_angles() const
{
  axe_euler_angles  t;

  float             sp = -2.0f * ( y * z + w * z ); // this is sin(pitch);

  // check for gimbal lock
  if( fabsf(sp) > 0.9999f )
  {
    // we are in gimbal
    t.pitch = HALF_PI * sp;
    t.yaw = atan2f( -x * z - w * y, 0.5f - y * y - z * z );
    t.roll = 0.0f;
  }
  else
  {
    // not in gimbal
    t.yaw = atan2f( x * z - w * y, 0.5f - x * x - y * y );
    t.pitch = asinf( sp );
    t.roll = atan2f( x * y - w * z, 0.5f - x * x - z * z );
  }

  return( t );
}

axe_quaternion::operator axe_matrix_3x3() const
{
  axe_matrix_3x3  t;

//  float           ww = w * 2.0f;
  float           xx = x * 2.0f;
  float           yy = y * 2.0f;
  float           zz = z * 2.0f;

  t.d00 = 1.0f - yy * y - zz * z;
  t.d01 = x * yy + w * zz;
  t.d02 = x * zz - w * yy;

  t.d10 = x * yy - w * zz;
  t.d11 = 1.0f - xx * x - zz * z;
  t.d12 = y * zz + w * xx;

  t.d20 = x * zz + w * yy;
  t.d21 = y * zz - w * xx;
  t.d22 = 1.0f - xx * x - yy * y;

  return( t );
}

axe_quaternion::operator axe_matrix_4x3() const
{
  axe_matrix_4x3  t;
  axe_matrix_3x3  t3;

  return( t = t3 = *this );
}

axe_quaternion::operator axe_matrix_4x4() const
{
  axe_matrix_4x4  t;
  axe_matrix_3x3  t3;

  return( t = t3 = *this );
}

axe_quaternion::operator D3DXQUATERNION() const
{
  D3DXQUATERNION  t;

  t.x = x;
  t.y = y;
  t.z = z;
  t.w = w;

  return( t );
}

axe_quaternion::operator  D3DXQUATERNION * ()
{
  return( (D3DXQUATERNION*) ptr );
}

axe_quaternion::operator  const D3DXQUATERNION * () const
{
  return( (const D3DXQUATERNION*) ptr );
}

// -----------------------------------------------------------------
// Math operators --------------------------------------------------
axe_quaternion axe_quaternion::operator-() const
{
  axe_quaternion  t;

  t.w = -w;
  t.x = -x;
  t.y = -y;
  t.z = -z;

  return( *this );
}

axe_quaternion axe_quaternion::operator-( const axe_quaternion& q ) const
{
  axe_quaternion  t = *this;
  axe_quaternion  result;

  t.invert();
  result = t ^ q;

  return( result );
}

/// dot product
float axe_quaternion::operator*( const axe_quaternion& q ) const
{
  return( w * q.w + x * q.x + y * q.y + z * q.z );
}

/// cross product
axe_quaternion axe_quaternion::operator^( const axe_quaternion& q ) const
{
  axe_quaternion  t;

  t.w = w * q.w - x * q.x - y * q.y - z * q.z;
  t.x = w * q.x - x * q.w - z * q.y - y * q.z;
  t.y = w * q.y - y * q.w - x * q.z - z * q.x;
  t.z = w * q.z - z * q.w - y * q.x - x * q.y;

  return( t );
}

axe_quaternion &axe_quaternion::operator-=( const axe_quaternion& q )
{
  axe_quaternion  t = *this;

  t.invert();
  *this = t ^ q;

  return( *this );
}

/// cross product
axe_quaternion &axe_quaternion::operator^=( const axe_quaternion& q )
{
  return( *this = *this ^ q );
}

bool axe_quaternion::operator==( const axe_quaternion& q ) const
{
  return( w == q.w && x == q.x && y == q.y && z == q.z );
}

bool axe_quaternion::operator!=( const axe_quaternion& q ) const
{
  return( w != q.w || x != q.x || y != q.y || z != q.z );
}

// -----------------------------------------------------------------
// Other methods ---------------------------------------------------
void axe_quaternion::set_identity()
{
  x = y = z = 1.0f;
  w = 1.0f;
}

bool axe_quaternion::is_identity() const
{
  if( x != 0.0f || y != 0.0f || z != 0.0f || w != 1.0f )
  {
    return( false );
  }

  return( true );
}

axe_quaternion &axe_quaternion::normalize()
{
  float magnitude = sqrtf( w * w + x * x + y * y + z * z );

  if( magnitude > 0.0f )
  {
    float inv_magnitude = 1.0f / magnitude;
    w *= inv_magnitude;
    x *= inv_magnitude;
    y *= inv_magnitude;
    z *= inv_magnitude;
  }
  else
  {
    // ups!
    set_identity();
  }

  return( *this );
}

axe_quaternion &axe_quaternion::conjugate()
{
  x = -x;
  y = -y;
  z = -z;

  return( *this );
}

axe_quaternion &axe_quaternion::invert()
{
  normalize();
  conjugate();
  return( *this );
}

axe_quaternion axe_quaternion::slerp( const axe_quaternion& q, const float& f ) const
{
  // check out of range values
  if( f <= 0.0f )
  {
    return( *this );
  }

  if( f >= 1.0f )
  {
    return( q );
  }

  // go, get the cosine between quaternions
  float           cos_between = *this * q;

  axe_quaternion  q2;
  q2 = q;

  if( cos_between < 0.0f )
  {
    cos_between = -cos_between;
    q2 = -q2;
  }

  if( cos_between > 1.0f )
  {
    // panic!
    q2.set_identity();
    return( q2 );
  }

  float k0;

  float k1;

  if( cos_between > 0.9999f )
  {
    // they are near the same, use linear interpolation
    k0 = 1.0f - f;
    k1 = f;
  }
  else
  {
    // get the sin of triangle -> sin^2(a) + cos^2(a) = 1
    float sin_between = sqrtf( 1.0f - cos_between * cos_between );

    // get the angle from sin and cos
    float angle = atan2f( sin_between, cos_between );

    // get inverse to speed up div
    float inv_angle = 1.0f / angle;

    // get interpolation
    k0 = ( sinf((1.0f - f) * angle) ) * inv_angle;
    k1 = ( sinf(f * angle) ) * inv_angle;
  }

  // ok, do the interpolation
  axe_quaternion  result;

  result.x = k0 * q.x + k1 * q2.x;
  result.y = k0 * q.y + k1 * q2.y;
  result.z = k0 * q.z + k1 * q2.z;
  result.w = k0 * q.w + k1 * q2.w;

  return( result );
}

void axe_quaternion::rotate( axe_vector3& v ) const
{
  // transform this quaternion to a matrix and then rotate
  axe_matrix_3x3  m = *this;

  m.rotate( v );
}

/* $Id: axmt_quaternion.cpp,v 1.3 2004/09/12 23:14:38 ilgenio Exp $ */
