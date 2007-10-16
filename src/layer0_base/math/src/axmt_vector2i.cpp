/**
* @file
* axe_vector2ii class code without optimizations (int version of axe_vector2i)
*/
#include "axmt_stdafx.h"

// -----------------------------------------------------------------
// Creators --------------------------------------------------------
axe_vector2i &axe_vector2i::create( const int& _x, const int& _y ) {
  x = _x;
  y = _y;
  return( *this );
}

axe_vector2i &axe_vector2i::create( const axe_vector2i& v ) {
  x = v.x;
  y = v.y;
  return( *this );
}

// -----------------------------------------------------------------
// Cast operators --------------------------------------------------
axe_vector2i::operator axe_vector2() const
{
  axe_vector2 t;

  t.x = (float) x;
  t.y = (float) y;
  return( t );
}

axe_vector2i::operator axe_vector3() const
{
  axe_vector3 t;

  t.x = (float) x;
  t.y = (float) y;
  t.z = 0.0f;
  return( t );
}

axe_vector2i::operator axe_vector4() const
{
  axe_vector4 t;

  t.x = (float) x;
  t.y = (float) y;
  t.z = 0.0f;
  t.w = 1.0f;
  return( t );
}

// -----------------------------------------------------------------
// Math operators --------------------------------------------------
axe_vector2i axe_vector2i::operator-() const
{
  axe_vector2i  t;
  t.x = -x;
  t.y = -y;
  return( t );
}

axe_vector2i axe_vector2i::operator+( const axe_vector2i& v ) const
{
  axe_vector2i  t;
  t.x = x + v.x;
  t.y = y + v.y;
  return( t );
}

axe_vector2i axe_vector2i::operator-( const axe_vector2i& v ) const
{
  axe_vector2i  t;
  t.x = x - v.x;
  t.y = y - v.y;
  return( t );
}

int axe_vector2i::operator*( const axe_vector2i& v ) const
{ /// dot product
  return( x * v.x + y * v.y );
}

axe_vector2i axe_vector2i::operator*( const int& a ) const
{
  axe_vector2i  t;
  t.x = x * a;
  t.y = y * a;
  return( t );
}

axe_vector2i axe_vector2i::operator/( const int& a ) const
{
  axe_vector2i  t;
  t.x = x / a;
  t.y = y / a;
  return( t );
}

axe_vector2i &axe_vector2i::operator+=( const axe_vector2i& v ) {
  x += v.x;
  y += v.y;
  return( *this );
}

axe_vector2i &axe_vector2i::operator-=( const axe_vector2i& v ) {
  x -= v.x;
  y -= v.y;
  return( *this );
}

axe_vector2i &axe_vector2i::operator*=( const int& a ) {
  x *= a;
  y *= a;
  return( *this );
}

axe_vector2i &axe_vector2i::operator/=( const int& a ) {
  x /= a;
  y /= a;
  return( *this );
}

bool axe_vector2i::operator==( const axe_vector2i& v ) const
{
  return( x == v.x && y == v.y );
}

bool axe_vector2i::operator!=( const axe_vector2i& v ) const
{
  return( x != v.x || y != v.y );
}

bool axe_vector2i::operator<( const axe_vector2i& v ) const
{
  return( (x + y) < (v.x + v.y) );
}

bool axe_vector2i::operator>( const axe_vector2i& v ) const
{
  return( (x + y) > (v.x + v.y) );
}

bool axe_vector2i::operator>=( const axe_vector2i& v ) const
{
  return( (x + y) >= (v.x + v.y) );
}

bool axe_vector2i::operator<=( const axe_vector2i& v ) const
{
  return( (x + y) <= (v.x + v.y) );
}

// -----------------------------------------------------------------
// Other methods ---------------------------------------------------
void axe_vector2i::zero() {
  x = y = 0;
}

void axe_vector2i::negate() {
  x = -x;
  y = -y;
}

float axe_vector2i::module() const
{
  return( sqrtf((float) (x * x + y * y)) );
}

float axe_vector2i::distance_to( const axe_vector2i& v ) const
{ /// euclidean distance
  int fx = x - v.x;
  int fy = y - v.y;
  return( sqrtf((float) (fx * fx + fy * fy)) );
}

float axe_vector2i::distance_pow2_to( const axe_vector2i& v) const 
{ /// euclidean distance ^2
  int fx = x - v.x;
  int fy = y - v.y;
  return( (float) (fx * fx + fy * fy) );
}

int axe_vector2i::distance_man_to( const axe_vector2i& v ) const
{ /// manhattan distance
  return( abs(v.x - x) + abs(v.y - y) );
}

/* $Id: axmt_vector2i.cpp,v 1.2 2004/07/21 22:08:51 doneval Exp $ */
