/**
* @file
*  axe_float struct
*/
#include "axmt_stdafx.h"

// -----------------------------------------------------------------
// Creators --------------------------------------------------------
axe_float::axe_float( const float& f )
{
  this->f = f;
}

// -----------------------------------------------------------------
// Cast operators --------------------------------------------------
axe_float::operator int() const
{
  return( (int) f );
}

axe_float::operator float() const
{
  return( f );
}

// -----------------------------------------------------------------
// Math operators --------------------------------------------------
bool axe_float::operator==( const axe_float& v ) const
{
  return( abs(f - v.f) < EPSILON );
}

bool axe_float::operator!=( const axe_float& v ) const
{
  return( abs(f - v.f) > EPSILON );
}

bool axe_float::operator>=( const axe_float& v ) const
{
  return( f > v.f || abs(f - v.f) < EPSILON );
}

bool axe_float::operator<=( const axe_float& v ) const
{
  return( f < v.f || abs(f - v.f) < EPSILON );
}

// -----------------------------------------------------------------
// Other methods ---------------------------------------------------
axe_float axe_float::set_infinity()
{
  f = INFINITY;
  return( *this );
}

axe_float axe_float::inverse() const
{
  return( axe_float(1.0f / f) );
}

axe_float axe_float::sin() const
{
  const float B = 4.0f / PI;
  const float C = -4.0f / QUAD_PI;
  float       y = B * f + C * f * abs( f );

#ifdef AXMT_EXTRA_PRECISION
  const float P = 0.225f;
  y = P * ( y * abs(y) - y ) + y;
#endif
  return( y );
}

axe_float axe_float::cos() const
{
  // cos(x) = sin(x + pi/2)
  axe_float s = f + HALF_PI;

  return( s.sin() );
}

axe_float axe_float::tan() const
{
  return( tanf(f) );
}

axe_float axe_float::asin() const
{
  return( asinf(f) );
}

axe_float axe_float::acos() const
{
  return( acosf(f) );
}

axe_float axe_float::atan() const
{
  return( atanf(f) );
}

axe_float axe_float::floor() const
{
  return( floorf(f) );
}

axe_float axe_float::set_max( axe_float& v )
{
  if( f > v.f )
  {
    f = v.f;
  }

  return( *this );
}

axe_float axe_float::set_min( axe_float& v )
{
  if( f < v.f )
  {
    f = v.f;
  }

  return( *this );
}

axe_float axe_float::cap( axe_float& min, axe_float& max )
{
  if( f < min.f )
  {
    f = min.f;
  }
  else if( f > max.f )
  {
    f = max.f;
  }

  return( *this );
}

/* $Id: axmt_angle.cpp,v 1.2 2004/08/31 07:45:20 doneval Exp $ */
