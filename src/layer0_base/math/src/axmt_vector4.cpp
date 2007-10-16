/**
* @file
* axe_vector4 class code without optimizations (only FU here)
*/
#include "axmt_stdafx.h"

// -----------------------------------------------------------------
// Creators --------------------------------------------------------
axe_vector4 &axe_vector4::create( const float& _x, const float& _y, const float& _z, const float& _w ) {
  x = _x;
  y = _y;
  z = _z;
  w = _w;
  return( *this );
}

axe_vector4 &axe_vector4::create( const axe_vector4& v ) {
  x = v.x;
  y = v.y;
  z = v.z;
  w = v.w;
  return( *this );
}

// -----------------------------------------------------------------
// Cast operators --------------------------------------------------
axe_vector4::operator axe_vector2i() const
{
  axe_vector2i  t;

  t.x = (int) x;
  t.y = (int) y;
  return( t );
}

axe_vector4::operator axe_vector2() const
{
  axe_vector2 t;

  t.x = x;
  t.y = y;
  return( t );
}

axe_vector4::operator axe_vector3() const
{
  axe_vector3 t;

  t.x = x;
  t.y = y;
  t.z = z;
  return( t );
}

axe_vector4::operator D3DXVECTOR4() const
{
  D3DXVECTOR4 t;

  t.x = x;
  t.y = y;
  t.z = z;
  t.w = w;
  return( t );
}

axe_vector4::operator D3DXVECTOR4 * () {
  return( (D3DXVECTOR4*) ptr );
}

axe_vector4::operator const D3DXVECTOR4 * () const
{
  return( (const D3DXVECTOR4*) ptr );
}

// -----------------------------------------------------------------
// Math operators --------------------------------------------------
axe_vector4 axe_vector4::operator-() const
{
  axe_vector4 t;
  t.x = -x;
  t.y = -y;
  t.z = -z;
  t.w = -w;
  return( t );
}

axe_vector4 axe_vector4::operator+( const axe_vector4& v ) const
{
  axe_vector4 t;
  t.x = x + v.x;
  t.y = y + v.y;
  t.z = z + v.z;
  t.w = w + v.w;
  return( t );
}

axe_vector4 axe_vector4::operator-( const axe_vector4& v ) const
{
  axe_vector4 t;
  t.x = x - v.x;
  t.y = y - v.y;
  t.z = y - v.z;
  t.w = w - v.w;
  return( t );
}

float axe_vector4::operator*( const axe_vector4& v ) const
{                                 /// dot product
  return( x * v.x + y * v.y + z * v.z );
}

axe_vector4 axe_vector4::operator*( const float& a ) const
{
  axe_vector4 t;
  t.x = x * a;
  t.y = y * a;
  t.z = z * a;
  return( t );
}

axe_vector4 axe_vector4::operator/( const float& a ) const
{
  float       f = 1.0f / a;
  axe_vector4 t;
  t.x = x * f;
  t.y = y * f;
  t.z = z * f;
  return( t );
}

axe_vector4 &axe_vector4::operator+=( const axe_vector4& v ) {
  x += v.x;
  y += v.y;
  z += v.z;
  return( *this );
}

axe_vector4 &axe_vector4::operator-=( const axe_vector4& v ) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return( *this );
}

axe_vector4 &axe_vector4::operator*=( const float& a ) {
  x *= a;
  y *= a;
  z *= a;
  return( *this );
}

axe_vector4 &axe_vector4::operator/=( const float& a ) {
  float f = 1.0f / a;             /// this can be hardware accelerated
  x *= f;
  y *= f;
  z *= f;
  return( *this );
}

bool axe_vector4::operator==( const axe_vector4& v ) const
{
  return( x == v.x && y == v.y && z == v.z && w == v.w );
}

bool axe_vector4::operator!=( const axe_vector4& v ) const
{
  return( x != v.x || y != v.y || z != v.z || w != v.w );
}

bool axe_vector4::operator<( const axe_vector4& v ) const
{
  return( (x + y + z) < (v.x + v.y + v.z) );
}

bool axe_vector4::operator>( const axe_vector4& v ) const
{
  return( (x + y + z) > (v.x + v.y + v.z) );
}

bool axe_vector4::operator>=( const axe_vector4& v ) const
{
  return( (x + y + z) >= (v.x + v.y + v.z) );
}

bool axe_vector4::operator<=( const axe_vector4& v ) const
{
  return( (x + y + z) <= (v.x + v.y + v.z) );
}

// -----------------------------------------------------------------
// Other methods ---------------------------------------------------
void axe_vector4::zero() {
  x = y = z = w = 0.0f;
}

void axe_vector4::normalize() {
  float m = x * x + y * y + z * z;
  if( m > 0.0f ) {
    float inv_m = 1 / sqrtf( m ); /// this can be very hardware optimized
    x *= inv_m;
    y *= inv_m;
    z *= inv_m;
    w = 1.0f;
  }
}

void axe_vector4::negate() {
  x = -x;
  y = -y;
  z = -z;
  w = -w;
}

float axe_vector4::module() const
{
  return( sqrtf(x * x + y * y + z * z) );
}

/**
* see http://www.flipcode.com/articles/article_fastdistance.shtml
*/
float axe_vector4::module_approx() const
{
  float min;

  float max;

  float approx;

  float dx;

  float dy;

  float dz;
  ( x < 0 ) ? dx = -x : dx = x;
  ( y < 0 ) ? dy = -y : dy = y;
  ( z < 0 ) ? dz = -z : dz = z;

  // todo ---------------------------
  if( dx < dy ) {
    min = dx;
    max = dy;
  } else {
    min = dy;
    max = dx;
  }

  approx = ( max * 1007 ) + ( min * 441 );

  //	if (max < ( min << 4 )) {
  if( max < (min * 16) ) {
    approx -= ( max * 40 );
  }

  // add 512 for proper rounding
  //return (( approx + 512 ) >> 10 );
  return( (approx + 512) / 1024 );

  // todo ---------------------------
}

float axe_vector4::distance_to( const axe_vector4& v ) const
{                                 /// euclidean distance
  float fx = x - v.x;
  float fy = y - v.y;
  float fz = z - v.z;
  return( sqrtf(fx * fx + fy * fy + fz * fz) );
}

float axe_vector4::distance_pow2_to( const axe_vector4& v ) const
{                                 /// euclidean distance ^2
  float fx = x - v.x;
  float fy = y - v.y;
  float fz = z - v.z;
  return( fx * fx + fy * fy + fz * fz );
}

float axe_vector4::distance_approx_to( const axe_vector4& v ) const
{                                 /// fast approx. distance
  axe_vector4 t;
  t.x = x - v.x;
  t.y = y - v.y;
  t.z = z - v.z;
  return( t.module_approx() );
}

float axe_vector4::distance_man_to( const axe_vector4& v ) const
{                                 /// manhattan distance
  return( fabsf(v.x - x) + fabsf(v.y - y) + fabsf(v.z - z) );
}

axe_vector4 axe_vector4::lerp( const axe_vector4& v, const float& factor ) const
{
  // check ranges
  if( factor <= 0.0f ) {
    return( *this );
  }

  if( factor >= 1.0f ) {
    return( v );
  }

  // go
  axe_vector4 result;

  float       one_minus_factor = 1.0f - factor;

  result.x = x * one_minus_factor + v.x * factor;
  result.y = y * one_minus_factor + v.y * factor;
  result.z = z * one_minus_factor + v.z * factor;
  result.w = w * one_minus_factor + v.w * factor;

  return( result );
}

/* $Id: axmt_vector4.cpp,v 1.2 2004/07/21 22:08:51 doneval Exp $ */
