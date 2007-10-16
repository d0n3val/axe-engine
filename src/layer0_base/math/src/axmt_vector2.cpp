/**
* @file
* axe_vector2 class code without optimizations (only FU here)
*/
#include "axmt_stdafx.h"

// -----------------------------------------------------------------
// Creators --------------------------------------------------------
axe_vector2 &axe_vector2::create( const float& _x, const float& _y ) {
  x = _x;
  y = _y;
  return( *this );
}

axe_vector2 &axe_vector2::create( const axe_vector2& v ) {
  x = v.x;
  y = v.y;
  return( *this );
}

// -----------------------------------------------------------------
// Cast operators --------------------------------------------------
axe_vector2::operator axe_vector2i() const
{
  axe_vector2i  t;

  t.x = (int) x;
  t.y = (int) y;
  return( t );
}

axe_vector2::operator axe_vector3() const
{
  axe_vector3 t;

  t.x = x;
  t.y = y;
  t.z = 0.0f;
  return( t );
}

axe_vector2::operator axe_vector4() const
{
  axe_vector4 t;

  t.x = x;
  t.y = y;
  t.z = 0.0f;
  t.w = 1.0f;
  return( t );
}

axe_vector2::operator D3DXVECTOR2() const
{
  D3DXVECTOR2 t;

  t.x = x;
  t.y = y;
  return( t );
}

axe_vector2::operator D3DXVECTOR2*  () {
  return( (D3DXVECTOR2*) ptr );
}

axe_vector2::operator const D3DXVECTOR2*  () const
{
  return( (CONST D3DXVECTOR2*) ptr );
}

// -----------------------------------------------------------------
// Math operators --------------------------------------------------
axe_vector2 axe_vector2::operator-() const
{
  axe_vector2 t;
  t.x = -x;
  t.y = -y;
  return( t );
}

axe_vector2 axe_vector2::operator+( const axe_vector2& v ) const
{
  axe_vector2 t;
  t.x = x + v.x;
  t.y = y + v.y;
  return( t );
}

axe_vector2 axe_vector2::operator-( const axe_vector2& v ) const
{
  axe_vector2 t;
  t.x = x - v.x;
  t.y = y - v.y;
  return( t );
}

/// dot product
float axe_vector2::operator*( const axe_vector2& v ) const
{
  return( x * v.x + y * v.y );
}

axe_vector2 axe_vector2::operator*( const float& a ) const
{
  axe_vector2 t;
  t.x = x * a;
  t.y = y * a;
  return( t );
}

axe_vector2 axe_vector2::operator/( const float& a ) const
{
  float       f = 1.0f / a;
  axe_vector2 t;
  t.x = x * f;
  t.y = y * f;
  return( t );
}

axe_vector2 &axe_vector2::operator+=( const axe_vector2& v ) {
  x += v.x;
  y += v.y;
  return( *this );
}

axe_vector2 &axe_vector2::operator-=( const axe_vector2& v ) {
  x -= v.x;
  y -= v.y;
  return( *this );
}

axe_vector2 &axe_vector2::operator*=( const float& a ) {
  x *= a;
  y *= a;
  return( *this );
}

axe_vector2 &axe_vector2::operator/=( const float& a ) {
  float f = 1.0f / a;
  x *= f;
  y *= f;
  return( *this );
}

bool axe_vector2::operator==( const axe_vector2& v ) const
{
  return( x == v.x && y == v.y );
}

bool axe_vector2::operator!=( const axe_vector2& v ) const
{
  return( x != v.x || y != v.y );
}

bool axe_vector2::operator<( const axe_vector2& v ) const
{
  return( (x + y) < (v.x + v.y) );
}

bool axe_vector2::operator>( const axe_vector2& v ) const
{
  return( (x + y) > (v.x + v.y) );
}

bool axe_vector2::operator>=( const axe_vector2& v ) const
{
  return( (x + y) >= (v.x + v.y) );
}

bool axe_vector2::operator<=( const axe_vector2& v ) const
{
  return( (x + y) <= (v.x + v.y) );
}

// -----------------------------------------------------------------
// Other methods ---------------------------------------------------
void axe_vector2::zero() {
  x = y = 0.0f;
}

void axe_vector2::normalize() {
  float m = x * x + y * y;
  if( m > 0.0f ) {
    float inv_m = 1 / sqrtf( m ); /// this can be very hardware optimized
    x *= inv_m;
    y *= inv_m;
  }
}

void axe_vector2::negate() {
  x = -x;
  y = -y;
}

float axe_vector2::module() const
{
  return( sqrtf(x * x + y * y) );
}

/**
 * see http://www.flipcode.com/articles/article_fastdistance.shtml
 */
float axe_vector2::module_approx() const
{
  float min;

  float max;

  float approx;

  float dx;

  float dy;
  ( x < 0 ) ? dx = -x : dx = x;
  ( y < 0 ) ? dy = -y : dy = y;

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
}

float axe_vector2::distance_to( const axe_vector2& v ) const
{                                 /// euclidean distance
  float fx = x - v.x;
  float fy = y - v.y;
  return( sqrtf(fx * fx + fy * fy) );
}

float axe_vector2::distance_pow2_to( const axe_vector2& v ) const
{                                 /// euclidean distance ^2
  float fx = x - v.x;
  float fy = y - v.y;
  return( fx * fx + fy * fy );
}

float axe_vector2::distance_approx_to( const axe_vector2& v ) const
{                                 /// fast approx. distance
  axe_vector2 t;
  t.x = x - v.x;
  t.y = y - v.y;
  return( t.module_approx() );
}

float axe_vector2::distance_man_to( const axe_vector2& v ) const
{                                 /// manhattan distance
  return( fabsf(v.x - x) + fabsf(v.y - y) );
}

axe_vector2 axe_vector2::lerp( const axe_vector2& v, const float& factor ) const
{
  // check ranges
  if( factor <= 0.0f ) {
    return( *this );
  }

  if( factor >= 1.0f ) {
    return( v );
  }

  // go
  axe_vector2 result;

  float       one_minus_factor = 1.0f - factor;

  result.x = x * one_minus_factor + v.x * factor;
  result.y = y * one_minus_factor + v.y * factor;

  return( result );
}

/* $Id: axmt_vector2.cpp,v 1.2 2004/07/21 22:08:51 doneval Exp $ */
