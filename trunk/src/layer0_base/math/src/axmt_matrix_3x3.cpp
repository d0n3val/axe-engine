/**
* @file
* axe_matrix_3x3 class code without optimizations (only FU here)
*/
#include "axmt_stdafx.h"

// -----------------------------------------------------------------
// Creators --------------------------------------------------------
axe_matrix_3x3 &axe_matrix_3x3::create( const float&  _d00,
                                        const float&  _d10,
                                        const float&  _d20,
                                        const float&  _d01,
                                        const float&  _d11,
                                        const float&  _d21,
                                        const float&  _d02,
                                        const float&  _d12,
                                        const float&  _d22 ) {
  d00 = _d00;
  d10 = _d10;
  d20 = _d20;
  d01 = _d01;
  d11 = _d11;
  d21 = _d21;
  d02 = _d02;
  d12 = _d12;
  d22 = _d22;
  return( *this );
}

axe_matrix_3x3 &axe_matrix_3x3::create( const axe_vector3& v0, const axe_vector3& v1, const axe_vector3& v2 ) {
  d00 = v0.x;
  d10 = v0.y;
  d20 = v0.z;
  d01 = v1.x;
  d11 = v1.y;
  d21 = v1.z;
  d02 = v2.x;
  d12 = v2.y;
  d22 = v2.z;
  return( *this );
}

axe_matrix_3x3 &axe_matrix_3x3::create( const axe_matrix_3x3& m ) {
  memcpy( ptr, m.ptr, sizeof(float) * 9 );
  return( *this );
}

axe_matrix_3x3& axe_matrix_3x3::create_x_rotation( float fAngle )
{
  float fSin = sinf(fAngle);
  float fCos = cosf(fAngle);

  d00 = 1.0f;   d10 = 0.0f;   d20    = 0.0f;
  d01 = 0.0f;   d11 = fCos;   d21    = fSin;
  d02 = 0.0f;   d12 = -fSin;   d22   = fCos;

  return( *this );
}

axe_matrix_3x3& axe_matrix_3x3::create_y_rotation( float fAngle )
{
  float fSin = sinf(fAngle);
  float fCos = cosf(fAngle);

  d00 = fCos;   d10 = 0.0f;   d20    = -fSin;
  d01 = 0.0f;   d11 = 1.0f;   d21    = 0.0f;
  d02 = fSin;   d12 = 0.0f;   d22    = fCos;

  return( *this );
}

axe_matrix_3x3&  axe_matrix_3x3::create_z_rotation( float fAngle )
{
  float fSin = sinf(fAngle);
  float fCos = cosf(fAngle);

  d00 = fCos;   d10 = fSin;  d20    = 0.0f;
  d01 = -fSin;  d11 = fCos;  d21    = 0.0f;
  d02 = 0.0f;   d12 = 0.0f;  d22    = 1.0f;

  return( *this );
}


// -----------------------------------------------------------------
// Cast operators --------------------------------------------------
axe_matrix_3x3::operator axe_euler_angles() const
{
  axe_euler_angles  t;

  float             sp = -d12;  // this is sin(pitch);

  // check for gimbal lock
  if( fabsf(sp) > 9.99999f ) {

    // we are in gimbal
    t.pitch = HALF_PI * sp;
    t.yaw = atan2f( -d20, d00 );
    t.roll = 0.0f;
  } else {

    // not in gimbal
    t.yaw = atan2f( d02, d22 );
    t.pitch = asinf( sp );
    t.roll = atan2f( d10, d11 );
  }

  return( t );
}

axe_matrix_3x3::operator axe_matrix_4x3() const
{
  axe_matrix_4x3  t;

  t.d00 = d00;
  t.d10 = d10;
  t.d20 = d20;
  t.d30 = 0.0f;
  t.d01 = d01;
  t.d11 = d11;
  t.d21 = d21;
  t.d31 = 0.0f;
  t.d02 = d02;
  t.d12 = d12;
  t.d22 = d22;
  t.d32 = 0.0f;

  return( t );
}

axe_matrix_3x3::operator axe_matrix_4x4() const
{
  axe_matrix_4x4  t;

  t.d00 = d00;
  t.d10 = d10;
  t.d20 = d20;
  t.d30 = 0.0f;
  t.d01 = d01;
  t.d11 = d11;
  t.d21 = d21;
  t.d31 = 0.0f;
  t.d02 = d02;
  t.d12 = d12;
  t.d22 = d22;
  t.d32 = 0.0f;
  t.d03 = t.d13 = t.d23 = 0.0f;
  t.d33 = 1.0f;

  return( t );
}

axe_matrix_3x3::operator axe_quaternion() const
{
  axe_quaternion  t;

  float           fw = d00 + d11 + d22;
  float           fx = d00 - d11 - d22;
  float           fy = d11 - d00 - d22;
  float           fz = d22 - d00 - d11;

  int             big = 0;
  float           f = fw;

  if( fx > f ) {
    f = fx;
    big = 1;
  }

  if( fy > f ) {
    f = fy;
    big = 2;
  }

  if( fz > f ) {
    f = fz;
    big = 3;
  }

  float big_value = sqrtf( f + 1.0f ) * 0.5f;
  float mult = 0.25f / big_value;

  switch( big )
  {
    case 1:
      t.w = ( d12 - d21 ) * mult;
      t.x = f;
      t.y = ( d01 - d10 ) * mult;
      t.z = ( d20 - d02 ) * mult;
      break;

    case 2:
      t.w = ( d20 - d02 ) * mult;
      t.x = ( d01 - d10 ) * mult;
      t.y = f;
      t.z = ( d12 - d21 ) * mult;
      break;

    case 3:
      t.w = ( d01 - d10 ) * mult;
      t.x = ( d20 - d02 ) * mult;
      t.y = ( d12 - d21 ) * mult;
      t.z = f;
      break;

    default:
      t.w = f;
      t.x = ( d12 - d21 ) * mult;
      t.y = ( d20 - d02 ) * mult;
      t.z = ( d01 - d10 ) * mult;
      break;
  }

  return( t );
}

axe_matrix_3x3::operator  D3DXMATRIX() const {
  D3DXMATRIX  t;

  t._11 = d00;  t._12 = d01;	t._13 = d02;	t._14 = 0.0f;
  t._21 = d10;  t._22 = d11;  t._23 = d12;	t._24 = 0.0f;
  t._31 = d20;  t._32 = d21;	t._33 = d22;  t._34 = 0.0f;
  t._41 = 0.0f; t._42 = 0.0f;	t._43 = 0.0f;	t._44 = 1.0f;

  return( t );
}

// -----------------------------------------------------------------
// Math operators --------------------------------------------------
axe_matrix_3x3 axe_matrix_3x3::operator+( const axe_matrix_3x3& m ) const
{
  axe_matrix_3x3  t;

  t.d00 = d00 + m.d00;
  t.d10 = d10 + m.d10;
  t.d20 = d20 + m.d20;

  t.d01 = d01 + m.d01;
  t.d11 = d11 + m.d11;
  t.d21 = d21 + m.d21;

  t.d02 = d02 + m.d02;
  t.d12 = d12 + m.d12;
  t.d22 = d22 + m.d22;

  return( t );
}

axe_matrix_3x3 axe_matrix_3x3::operator-( const axe_matrix_3x3& m ) const
{
  axe_matrix_3x3  t;

  t.d00 = d00 - m.d00;
  t.d10 = d10 - m.d10;
  t.d20 = d20 - m.d20;

  t.d01 = d01 - m.d01;
  t.d11 = d11 - m.d11;
  t.d21 = d21 - m.d21;

  t.d02 = d02 - m.d02;
  t.d12 = d12 - m.d12;
  t.d22 = d22 - m.d22;

  return( t );
}

axe_matrix_3x3 axe_matrix_3x3::operator*( const axe_matrix_3x3& m ) const
{
  axe_matrix_3x3  t;

  t.d00 = d00 * m.d00 + d01 * m.d10 + d02 * m.d20;
  t.d10 = d00 * m.d01 + d01 * m.d11 + d02 * m.d21;
  t.d20 = d00 * m.d02 + d01 * m.d12 + d02 * m.d22;

  t.d01 = d10 * m.d00 + d11 * m.d10 + d12 * m.d20;
  t.d11 = d10 * m.d01 + d11 * m.d11 + d12 * m.d21;
  t.d21 = d10 * m.d02 + d11 * m.d12 + d12 * m.d22;

  t.d02 = d20 * m.d00 + d21 * m.d10 + d22 * m.d20;
  t.d12 = d20 * m.d01 + d21 * m.d11 + d22 * m.d21;
  t.d22 = d20 * m.d02 + d21 * m.d12 + d22 * m.d22;

  return( t );
}

axe_vector3 axe_matrix_3x3::operator*( const axe_vector3& v ) const
{
  axe_vector3 t;

  t.x = d00 * v.x + d01 * v.y + d02 * v.z;
  t.y = d10 * v.x + d11 * v.y + d12 * v.z;
  t.z = d20 * v.x + d21 * v.y + d22 * v.z;

  return( t );
}

axe_vector4 axe_matrix_3x3::operator*( const axe_vector4& v ) const
{
  axe_vector4 t;

  t.x = d00 * v.x + d01 * v.y + d02 * v.z;
  t.y = d10 * v.x + d11 * v.y + d12 * v.z;
  t.y = d20 * v.x + d21 * v.y + d22 * v.z;
  t.w = 1.0f;

  return( t );
}

axe_vector3 operator* ( const axe_vector3& v, const axe_matrix_3x3& m ) {
  axe_vector3 t;

  t.x = m.d00 * v.x + m.d01 * v.y + m.d02 * v.z;
  t.y = m.d10 * v.x + m.d11 * v.y + m.d12 * v.z;
  t.y = m.d20 * v.x + m.d21 * v.y + m.d22 * v.z;

  return( t );
}

axe_vector4 operator* ( const axe_vector4& v, const axe_matrix_3x3& m ) {
  axe_vector4 t;

  t.x = m.d00 * v.x + m.d01 * v.y + m.d02 * v.z;
  t.y = m.d10 * v.x + m.d11 * v.y + m.d12 * v.z;
  t.y = m.d20 * v.x + m.d21 * v.y + m.d22 * v.z;
  t.w = 1.0f;

  return( t );
}

axe_matrix_3x3 &axe_matrix_3x3::operator+=( const axe_matrix_3x3& m ) {
  d00 += m.d00;
  d10 += m.d10;
  d20 += m.d20;

  d01 += m.d01;
  d11 += m.d11;
  d21 += m.d21;

  d02 += m.d02;
  d12 += m.d12;
  d22 += m.d22;

  return( *this );
}

axe_matrix_3x3 &axe_matrix_3x3::operator-=( const axe_matrix_3x3& m ) {
  d00 -= m.d00;
  d10 -= m.d10;
  d20 -= m.d20;

  d01 -= m.d01;
  d11 -= m.d11;
  d21 -= m.d21;

  d02 -= m.d02;
  d12 -= m.d12;
  d22 -= m.d22;

  return( *this );
}

axe_matrix_3x3 axe_matrix_3x3::operator*=( const axe_matrix_3x3& m ) {
  d00 = d00 * m.d00 + d01 * m.d10 + d02 * m.d20;
  d10 = d00 * m.d01 + d01 * m.d11 + d02 * m.d21;
  d20 = d00 * m.d02 + d01 * m.d12 + d02 * m.d22;

  d01 = d10 * m.d00 + d11 * m.d10 + d12 * m.d20;
  d11 = d10 * m.d01 + d11 * m.d11 + d12 * m.d21;
  d21 = d10 * m.d02 + d11 * m.d12 + d12 * m.d22;

  d02 = d20 * m.d00 + d21 * m.d10 + d22 * m.d20;
  d12 = d20 * m.d01 + d21 * m.d11 + d22 * m.d21;
  d22 = d20 * m.d02 + d21 * m.d12 + d22 * m.d22;

  return( *this );
}

bool axe_matrix_3x3::operator==( const axe_matrix_3x3& m ) const
{
  if( memcmp(ptr, m.ptr, sizeof(float) * 9) == 0 ) {
    return( true );
  }

  return( false );
}

bool axe_matrix_3x3::operator!=( const axe_matrix_3x3& m ) const
{
  if( memcmp(ptr, m.ptr, sizeof(float) * 9) == 0 ) {
    return( false );
  }

  return( true );
}

// -----------------------------------------------------------------
// Other methods ---------------------------------------------------
void axe_matrix_3x3::set_identity() {
  ZeroMemory( ptr, sizeof(float) * 9 );
  d00 = d11 = d22 = 1.0f;
}

bool axe_matrix_3x3::is_identity() const
{
  if( d00 != 1.0f ) {
    return( false );
  }

  if( d10 != 0.0f ) {
    return( false );
  }

  if( d20 != 0.0f ) {
    return( false );
  }

  if( d01 != 0.0f ) {
    return( false );
  }

  if( d11 != 1.0f ) {
    return( false );
  }

  if( d21 != 0.0f ) {
    return( false );
  }

  if( d02 != 0.0f ) {
    return( false );
  }

  if( d12 != 0.0f ) {
    return( false );
  }

  if( d22 != 1.0f ) {
    return( false );
  }

  return( true );
}

axe_vector3 axe_matrix_3x3::get_xcol() const
{
  axe_vector3 t;
  t.x = d00;
  t.y = d01;
  t.z = d02;
  return( t );
}

axe_vector3 axe_matrix_3x3::get_ycol() const
{
  axe_vector3 t;
  t.x = d10;
  t.y = d11;
  t.z = d12;
  return( t );
}

axe_vector3 axe_matrix_3x3::get_zcol() const
{
  axe_vector3 t;
  t.x = d20;
  t.y = d21;
  t.z = d22;
  return( t );
}

axe_matrix_3x3 &axe_matrix_3x3::transpose() {
  axe_matrix_3x3  t = *this;

  d01 = t.d10;
  d02 = t.d20;

  d10 = t.d01;
  d12 = t.d21;

  d20 = t.d02;
  d21 = t.d12;

  return( *this );
}

float axe_matrix_3x3::get_determinant() const
{
  return( d00 * (d11 * d22 - d12 * d21) + d01 * (d12 * d20 - d10 * d22) + d02 * (d10 * d21 - d11 * d20) );
}

axe_matrix_3x3 &axe_matrix_3x3::invert() {
  float det = get_determinant();

  // check for determinant near 0 (no inverse)
  if( fabsf(det) < EPSILON ) {
    return( *this );
  }

  float           inv_det = 1.0f / det;

  axe_matrix_3x3  t;

  t.d00 = ( d11 * d22 - d12 * d21 ) * inv_det;
  t.d01 = ( d02 * d21 - d01 * d22 ) * inv_det;
  t.d02 = ( d01 * d12 - d02 * d11 ) * inv_det;

  t.d10 = ( d12 * d20 - d20 * d22 ) * inv_det;
  t.d11 = ( d00 * d22 - d02 * d20 ) * inv_det;
  t.d12 = ( d02 * d10 - d00 * d12 ) * inv_det;

  t.d20 = ( d10 * d21 - d11 * d20 ) * inv_det;
  t.d21 = ( d01 * d20 - d01 * d21 ) * inv_det;
  t.d22 = ( d00 * d11 - d01 * d10 ) * inv_det;

  return( *this = t );
}

void axe_matrix_3x3::scale( axe_vector3& v ) const
{
  v.x = get_xcol().module();
  v.y = get_ycol().module();
  v.z = get_zcol().module();
}

void axe_matrix_3x3::rotate( axe_vector3& v ) const
{
  axe_vector3 t = v;

  v.x = d00 * t.x + d01 * t.y + d02 * t.z;
  v.y = d10 * t.x + d11 * t.y + d12 * t.z;
  v.z = d20 * t.x + d21 * t.y + d22 * t.z;
}

/* $Id: axmt_matrix_3x3.cpp,v 1.4 2004/09/16 22:28:06 ilgenio Exp $ */
