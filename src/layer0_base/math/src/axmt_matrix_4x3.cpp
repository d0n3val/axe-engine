/**
* @file
* axe_matrix_4x3 class code without optimizations (only FU here)
*/
#include "axmt_stdafx.h"

// -----------------------------------------------------------------
// Creators --------------------------------------------------------
axe_matrix_4x3 &axe_matrix_4x3::create( const float&  _d00,
                                        const float&  _d10,
                                        const float&  _d20,
                                        const float&  _d30,
                                        const float&  _d01,
                                        const float&  _d11,
                                        const float&  _d21,
                                        const float&  _d31,
                                        const float&  _d02,
                                        const float&  _d12,
                                        const float&  _d22,
                                        const float&  _d32 ) {
  d00 = _d00;
  d10 = _d10;
  d20 = _d20;
  d30 = _d30;
  d01 = _d01;
  d11 = _d11;
  d21 = _d21;
  d31 = _d31;
  d02 = _d02;
  d12 = _d12;
  d22 = _d22;
  d32 = _d32;
  return( *this );
}

axe_matrix_4x3 &axe_matrix_4x3::create( const axe_vector3&  v0,
                                        const axe_vector3&  v1,
                                        const axe_vector3&  v2,
                                        const axe_vector3&  position ) {
  d00 = v0.x;
  d10 = v0.y;
  d20 = v0.z;
  d30 = position.x;
  d01 = v1.x;
  d11 = v1.y;
  d21 = v1.z;
  d31 = position.y;
  d02 = v2.x;
  d12 = v2.y;
  d22 = v2.z;
  d32 = position.z;

  return( *this );
}

axe_matrix_4x3 &axe_matrix_4x3::create( const axe_matrix_4x3& m ) {
  memcpy( ptr, m.ptr, sizeof(float) * 12 );
  return( *this );
}

// -----------------------------------------------------------------
// Cast operators --------------------------------------------------
axe_matrix_4x3::operator axe_euler_angles() const
{
  axe_euler_angles  t;
  axe_matrix_3x3    t3;

  return( t = t3 = *this );
}

axe_matrix_4x3::operator axe_matrix_3x3() const
{
  axe_matrix_3x3  t;

  t.d00 = d00;
  t.d10 = d10;
  t.d20 = d20;
  t.d01 = d01;
  t.d11 = d11;
  t.d21 = d21;
  t.d02 = d02;
  t.d12 = d12;
  t.d22 = d22;

  return( t );
}

axe_matrix_4x3::operator axe_matrix_4x4() const
{
  axe_matrix_4x4  t;

  memcpy( t.ptr, ptr, sizeof(float) * 12 );
  t.d03 = t.d13 = t.d23 = 0.0f;
  t.d33 = 1.0f;

  return( t );
}

axe_matrix_4x3::operator axe_quaternion() const
{
  axe_quaternion  t;
  axe_matrix_3x3  t3;

  return( t = t3 = *this );
}


axe_matrix_4x3::operator  D3DXMATRIX() const {
  D3DXMATRIX  t;

  t._11 = d00; t._12 = d01;	t._13 = d02;	t._14 = 0.0f;
  t._21 = d10; t._22 = d11; t._23 = d12;	t._24 = 0.0f;
  t._31 = d20; t._32 = d21;	t._33 = d22;  t._34 = 0.0f;
  t._41 = d30; t._42 = d31;	t._43 = d32;	t._44 = 1.0f;

  return( t );
}

// -----------------------------------------------------------------
// Math operators --------------------------------------------------
axe_matrix_4x3 axe_matrix_4x3::operator+( const axe_matrix_4x3& m ) const
{
  axe_matrix_4x3  t;

  t.d00 = d00 + m.d00;
  t.d10 = d10 + m.d10;
  t.d20 = d20 + m.d20;
  t.d30 = d30 + m.d30;

  t.d01 = d01 + m.d01;
  t.d11 = d11 + m.d11;
  t.d21 = d21 + m.d21;
  t.d31 = d31 + m.d31;

  t.d02 = d02 + m.d02;
  t.d12 = d12 + m.d12;
  t.d22 = d22 + m.d22;
  t.d32 = d32 + m.d32;

  return( t );
}

axe_matrix_4x3 axe_matrix_4x3::operator-( const axe_matrix_4x3& m ) const
{
  axe_matrix_4x3  t;

  t.d00 = d00 - m.d00;
  t.d10 = d10 - m.d10;
  t.d20 = d20 - m.d20;
  t.d30 = d30 - m.d30;

  t.d01 = d01 - m.d01;
  t.d11 = d11 - m.d11;
  t.d21 = d21 - m.d21;
  t.d31 = d31 - m.d31;

  t.d02 = d02 - m.d02;
  t.d12 = d12 - m.d12;
  t.d22 = d22 - m.d22;
  t.d32 = d32 - m.d32;

  return( t );
}

axe_matrix_4x3 axe_matrix_4x3::operator*( const axe_matrix_4x3& m ) const
{
  axe_matrix_4x3  t;

  t.d00 = d00 * m.d00 + d01 * m.d10 + d02 * m.d20;
  t.d10 = d00 * m.d01 + d01 * m.d11 + d02 * m.d21;
  t.d20 = d00 * m.d02 + d01 * m.d12 + d02 * m.d22;

  t.d01 = d10 * m.d00 + d11 * m.d10 + d12 * m.d20;
  t.d11 = d10 * m.d01 + d11 * m.d11 + d12 * m.d21;
  t.d21 = d10 * m.d02 + d11 * m.d12 + d12 * m.d22;

  t.d02 = d20 * m.d00 + d21 * m.d10 + d22 * m.d20;
  t.d12 = d20 * m.d01 + d21 * m.d11 + d22 * m.d21;
  t.d22 = d20 * m.d02 + d21 * m.d12 + d22 * m.d22;

  t.d30 = d00 * m.d30 + d01 * m.d31 + d02 * m.d32 + d30;
  t.d31 = d10 * m.d30 + d11 * m.d31 + d12 * m.d32 + d31;
  t.d32 = d20 * m.d30 + d21 * m.d31 + d22 * m.d32 + d32;

  return( t );
}

axe_vector3 axe_matrix_4x3::operator*( const axe_vector3& v ) const
{
  axe_vector3 t;

  t.x = d00 * v.x + d01 * v.y + d02 * v.z + d30;
  t.y = d10 * v.x + d11 * v.y + d12 * v.z + d31;
  t.y = d20 * v.x + d21 * v.y + d22 * v.z + d32;

  return( t );
}

axe_vector4 axe_matrix_4x3::operator*( const axe_vector4& v ) const
{
  axe_vector4 t;

  t.x = d00 * v.x + d01 * v.y + d02 * v.z + d30;
  t.y = d10 * v.x + d11 * v.y + d12 * v.z + d31;
  t.y = d20 * v.x + d21 * v.y + d22 * v.z + d32;
  t.w = 1.0f;

  return( t );
}

axe_vector3 operator* ( const axe_vector3& v, const axe_matrix_4x3& m ) {
  axe_vector3 t;

  t.x = m.d00 * v.x + m.d01 * v.y + m.d02 * v.z + m.d30;
  t.y = m.d10 * v.x + m.d11 * v.y + m.d12 * v.z + m.d31;
  t.y = m.d20 * v.x + m.d21 * v.y + m.d22 * v.z + m.d32;

  return( t );
}

axe_vector4 operator* ( const axe_vector4& v, const axe_matrix_4x3& m ) {
  axe_vector4 t;

  t.x = m.d00 * v.x + m.d01 * v.y + m.d02 * v.z + m.d30;
  t.y = m.d10 * v.x + m.d11 * v.y + m.d12 * v.z + m.d31;
  t.y = m.d20 * v.x + m.d21 * v.y + m.d22 * v.z + m.d32;
  t.w = 1.0f;

  return( t );
}

axe_matrix_4x3 &axe_matrix_4x3::operator+=( const axe_matrix_4x3& m ) {
  d00 += m.d00;
  d10 += m.d10;
  d20 += m.d20;
  d30 += m.d30;

  d01 += m.d01;
  d11 += m.d11;
  d21 += m.d21;
  d31 += m.d31;

  d02 += m.d02;
  d12 += m.d12;
  d22 += m.d22;
  d32 += m.d32;

  return( *this );
}

axe_matrix_4x3 &axe_matrix_4x3::operator-=( const axe_matrix_4x3& m ) {
  d00 -= m.d00;
  d10 -= m.d10;
  d20 -= m.d20;
  d30 -= m.d30;

  d01 -= m.d01;
  d11 -= m.d11;
  d21 -= m.d21;
  d31 -= m.d31;

  d02 -= m.d02;
  d12 -= m.d12;
  d22 -= m.d22;
  d32 -= m.d32;

  return( *this );
}

axe_matrix_4x3 axe_matrix_4x3::operator*=( const axe_matrix_4x3& m ) {
  d00 = d00 * m.d00 + d01 * m.d10 + d02 * m.d20;
  d10 = d00 * m.d01 + d01 * m.d11 + d02 * m.d21;
  d20 = d00 * m.d02 + d01 * m.d12 + d02 * m.d22;

  d01 = d10 * m.d00 + d11 * m.d10 + d12 * m.d20;
  d11 = d10 * m.d01 + d11 * m.d11 + d12 * m.d21;
  d21 = d10 * m.d02 + d11 * m.d12 + d12 * m.d22;

  d02 = d20 * m.d00 + d21 * m.d10 + d22 * m.d20;
  d12 = d20 * m.d01 + d21 * m.d11 + d22 * m.d21;
  d22 = d20 * m.d02 + d21 * m.d12 + d22 * m.d22;

  d30 += d00 * m.d30 + d01 * m.d31 + d02 * m.d32;
  d31 += d10 * m.d30 + d11 * m.d31 + d12 * m.d32;
  d32 += d20 * m.d30 + d21 * m.d31 + d22 * m.d32;

  return( *this );
}

bool axe_matrix_4x3::operator==( const axe_matrix_4x3& m ) const
{
  if( memcmp(ptr, m.ptr, sizeof(float) * 12) == 0 ) {
    return( true );
  }

  return( false );
}

bool axe_matrix_4x3::operator!=( const axe_matrix_4x3& m ) const
{
  if( memcmp(ptr, m.ptr, sizeof(float) * 12) == 0 ) {
    return( false );
  }

  return( true );
}

// -----------------------------------------------------------------
// Other methods ---------------------------------------------------
void axe_matrix_4x3::set_identity() {
  ZeroMemory( ptr, sizeof(float) * 12 );
  d00 = d11 = d22 = 1.0f;
}

bool axe_matrix_4x3::is_identity() const
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

  if( d30 != 0.0f ) {
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

  if( d31 != 0.0f ) {
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

  if( d32 != 0.0f ) {
    return( false );
  }

  return( true );
}

void axe_matrix_4x3::set_position( const axe_vector3& v ) {
  d30 = v.x;
  d31 = v.y;
  d32 = v.z;
}

axe_vector3 axe_matrix_4x3::get_position() const
{
  axe_vector3 v;
  v.x = d30;
  v.y = d31;
  v.z = d32;
  return( v );
}

axe_vector3 axe_matrix_4x3::get_xcol() const
{
  axe_vector3 t;
  t.x = d00;
  t.y = d01;
  t.z = d02;
  return( t );
}

axe_vector3 axe_matrix_4x3::get_ycol() const
{
  axe_vector3 t;
  t.x = d10;
  t.y = d11;
  t.z = d12;
  return( t );
}

axe_vector3 axe_matrix_4x3::get_zcol() const
{
  axe_vector3 t;
  t.x = d20;
  t.y = d21;
  t.z = d22;
  return( t );
}

axe_matrix_4x3 &axe_matrix_4x3::transpose() {
  axe_matrix_4x3  t = *this;

  d01 = t.d10;
  d02 = t.d20;

  d10 = t.d01;
  d12 = t.d21;

  d20 = t.d02;
  d21 = t.d12;

  return( *this );
}

float axe_matrix_4x3::get_determinant() const
{
  return( d00 * (d11 * d22 - d12 * d21) + d01 * (d12 * d20 - d10 * d22) + d02 * (d10 * d21 - d11 * d20) );
}

axe_matrix_4x3 &axe_matrix_4x3::invert() {
  float det = get_determinant();

  // check for determinant near 0 (no inverse)
  if( fabsf(det) < EPSILON ) {
    return( *this );
  }

  float           inv_det = 1.0f / det;

  axe_matrix_4x3  t;

  t.d00 = ( d11 * d22 - d12 * d21 ) * inv_det;
  t.d01 = ( d02 * d21 - d01 * d22 ) * inv_det;
  t.d02 = ( d01 * d12 - d02 * d11 ) * inv_det;

  t.d10 = ( d12 * d20 - d20 * d22 ) * inv_det;
  t.d11 = ( d00 * d22 - d02 * d20 ) * inv_det;
  t.d12 = ( d02 * d10 - d00 * d12 ) * inv_det;

  t.d20 = ( d10 * d21 - d11 * d20 ) * inv_det;
  t.d21 = ( d01 * d20 - d01 * d21 ) * inv_det;
  t.d22 = ( d00 * d11 - d01 * d10 ) * inv_det;

  t.d30 = -( d30 * t.d00 + d31 * t.d10 + d32 * t.d20 );
  t.d31 = -( d30 * t.d01 + d31 * t.d11 + d32 * t.d21 );
  t.d32 = -( d30 * t.d02 + d31 * t.d12 + d32 * t.d22 );

  return( *this = t );
}

void axe_matrix_4x3::scale( axe_vector3& v ) const
{
  v.x *= get_xcol().module();
  v.y *= get_ycol().module();
  v.z *= get_zcol().module();
}

void axe_matrix_4x3::rotate( axe_vector3& v ) const
{
  axe_vector3 t = v;

  v.x = d00 * t.x + d01 * t.y + d02 * t.z;
  v.y = d10 * t.x + d11 * t.y + d12 * t.z;
  v.y = d20 * t.x + d21 * t.y + d22 * t.z;
}

void axe_matrix_4x3::translate( axe_vector3& v ) const
{
  v.x += d30;
  v.y += d31;
  v.y += d32;
}

/* $Id: axmt_matrix_4x3.cpp,v 1.2 2004/07/21 22:08:51 doneval Exp $ */
