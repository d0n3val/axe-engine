/**
* @file
*  axe_angle class code without optimizations (only FPU here)
*/
#include "axmt_stdafx.h"

// -----------------------------------------------------------------
// Creators --------------------------------------------------------
axe_angle::axe_angle( const float& rad ) : radians( rad )
{
  wrap_pi();
}

axe_angle::axe_angle( const axe_angle& angle ) : radians( angle.radians )
{
}

axe_angle &axe_angle::create_deg( const float& degrees )
{
  radians = DEG_TO_RAD * degrees;
  return( *this );
}

axe_angle &axe_angle::create( const axe_vector2i& vector2 )
{
  radians = atan2f( (float) vector2.x, (float) vector2.y );
  return( *this );
}

axe_angle &axe_angle::create( const axe_vector2& vector2 )
{
  radians = atan2f( vector2.x, vector2.y );
  return( *this );
}

// -----------------------------------------------------------------
// Cast operators --------------------------------------------------
axe_angle::operator float() const
{
  return( radians );
}

axe_angle::operator axe_vector2i() const
{
  axe_vector2i  v;
  v.x = radians.cos();
  v.y = radians.sin();
  return( v );
}

axe_angle::operator axe_vector2() const
{
  axe_vector2 v;
  v.x = radians.cos();
  v.y = radians.sin();
  v.normalize();
  return( v );
}

axe_angle::operator axe_vector3() const
{
  axe_vector3 v;
  v.zero();
  v.x = radians.cos();
  v.y = radians.sin();
  v.normalize();
  return( v );
}

axe_angle::operator axe_vector4() const
{
  axe_vector4 v;
  v.zero();
  v.x = radians.cos();
  v.y = radians.sin();
  v.normalize();
  return( v );
}

// -----------------------------------------------------------------
// Math operators --------------------------------------------------
axe_angle axe_angle::operator-() const
{
  axe_angle r( -radians.f );
  return( r );
}

axe_angle axe_angle::operator+( const axe_angle& angle ) const
{
  axe_angle r( radians.f + angle.radians.f );
  r.wrap_pi();
  return( r );
}

axe_angle axe_angle::operator-( const axe_angle& angle ) const
{
  axe_angle r( radians.f - angle.radians.f );
  r.wrap_pi();
  return( r );
}

axe_angle axe_angle::operator*( const float& a ) const
{
  axe_angle r( radians.f * a );
  r.wrap_pi();
  return( r );
}

axe_angle axe_angle::operator/( const float& a ) const
{
  axe_angle r( radians.f / a );
  r.wrap_pi();
  return( r );
}

axe_angle &axe_angle::operator+=( const axe_angle& angle )
{
  radians.f += angle.radians.f;
  wrap_pi();
  return( *this );
}

axe_angle &axe_angle::operator-=( const axe_angle& angle )
{
  radians.f -= angle.radians.f;
  wrap_pi();
  return( *this );
}

axe_angle &axe_angle::operator/=( const float& a )
{
  radians.f /= a;
  wrap_pi();
  return( *this );
}

axe_angle &axe_angle::operator*=( const float& a )
{
  radians.f *= a;
  wrap_pi();
  return( *this );
}

bool axe_angle::operator==( const axe_angle& angle ) const
{
  return( radians == angle.radians );
}

bool axe_angle::operator!=( const axe_angle& angle ) const
{
  return( radians != angle.radians );
}

bool axe_angle::operator<( const axe_angle& angle ) const
{
  return( radians.f < angle.radians.f );
}

bool axe_angle::operator>( const axe_angle& angle ) const
{
  return( radians.f > angle.radians.f );
}

bool axe_angle::operator>=( const axe_angle& angle ) const
{
  return( radians >= angle.radians );
}

bool axe_angle::operator<=( const axe_angle& angle ) const
{
  return( radians <= angle.radians );
}

// -----------------------------------------------------------------
// Other methods ---------------------------------------------------
void axe_angle::zero()
{
  radians = 0;
}

float axe_angle::wrap_pi()
{
  float a = radians.f + PI;
  a -= floorf( a * INV_TWO_PI ) * TWO_PI;

  return( a - PI );
}

float axe_angle::get_deg() const
{
  return( radians.f * RAD_TO_DEG );
}

axe_angle axe_angle::get_left_perpendicular() const
{
  return( axe_angle(radians.f + HALF_PI) );
}

axe_angle axe_angle::get_right_perpendicular() const
{
  return( axe_angle(radians.f - HALF_PI) );
}

axe_angle axe_angle::get_opposite() const
{
  return( axe_angle(radians.f + PI) );
}

int axe_angle::is_in_front( const axe_angle& angle, float aperture ) const
{
  return( angle.is_between(axe_angle(radians.f + aperture), axe_angle(radians.f - aperture)) );
}

int axe_angle::is_behind( const axe_angle& angle, float aperture ) const
{
  axe_angle t = get_opposite();
  return( angle.is_between(axe_angle(t.radians.f + aperture), axe_angle(t.radians.f - aperture)) );
}

int axe_angle::is_on_the_left( const axe_angle& angle, float aperture ) const
{
  return( angle.is_between(axe_angle(radians.f + HALF_PI + aperture), axe_angle(radians.f + HALF_PI - aperture)) );
}

int axe_angle::is_on_the_right( const axe_angle& angle, float aperture ) const
{
  return( angle.is_between(axe_angle(radians.f - HALF_PI + aperture), axe_angle(radians.f - HALF_PI - aperture)) );
}

axmt_side axe_angle::find_side( const axe_angle& angle, float aperture ) const
{
  if( is_in_front(angle, aperture) == AXE_TRUE )
  {
    return( AXMT_FRONT );
  }
  else if( is_behind(angle, aperture) == AXE_TRUE )
  {
    return( AXMT_BEHIND );
  }
  else if( is_on_the_left(angle) == AXE_TRUE )
  {
    return( AXMT_LEFT );
  }
  else
  {
    return( AXMT_RIGHT );
  }
}

// Argument order is important, clockwise angle selection from first angle to the second one
int axe_angle::is_between( const axe_angle& angle1, const axe_angle& angle2 ) const
{
  return( radians <= angle1.radians && radians >= angle2.radians );
}

// Shortest distance to
axe_angle axe_angle::distance_to( const axe_angle& angle ) const
{
  return( axe_angle(radians.f - angle.radians.f) );
}

/* $Id: axmt_angle.cpp,v 1.2 2004/08/31 07:45:20 doneval Exp $ */
