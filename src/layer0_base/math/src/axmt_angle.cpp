/**
* @file
*  axe_angle class code without optimizations (only FPU here)
*/
#include "axmt_stdafx.h"

// -----------------------------------------------------------------
// Creators --------------------------------------------------------
axe_angle &axe_angle::create_deg( const float& degrees ) {
  radians = DEG_TO_RAD * degrees;
  return( *this );
}

axe_angle &axe_angle::create( const axe_vector2i& vector2 ) {
  radians = atan2f((float) vector2.x, (float) vector2.y);
  return( *this );
}

axe_angle &axe_angle::create( const axe_vector2& vector2 ) {
  radians = atan2f(vector2.x, vector2.y);
  return( *this );
}

// -----------------------------------------------------------------
// Cast operators --------------------------------------------------
axe_angle::operator  axe_vector2i() const {

}

axe_angle::operator  axe_vector2() const {

}

axe_angle::operator  axe_vector3() const {

}

axe_angle::operator  axe_vector4() const {

}

// -----------------------------------------------------------------
// Math operators --------------------------------------------------
axe_euler_angles axe_euler_angles::operator-() const
{
  axe_euler_angles  e;
  e.yaw = -yaw;
  e.pitch = -pitch;
  e.roll = -roll;
  return( e );
}

axe_euler_angles axe_euler_angles::operator+( const axe_euler_angles& e ) const
{
  axe_euler_angles  t;
  t.yaw = yaw + e.yaw;
  t.pitch = pitch + e.pitch;
  t.roll = roll + e.roll;
  t.canonize();
  return( t );
}

axe_euler_angles axe_euler_angles::operator-( const axe_euler_angles& e ) const
{
  axe_euler_angles  t;
  t.yaw = yaw - e.yaw;
  t.pitch = pitch - e.pitch;
  t.roll = roll - e.roll;
  t.canonize();
  return( t );
}

axe_euler_angles &axe_euler_angles::operator+=( const axe_euler_angles& e ) {
  yaw += e.yaw;
  pitch += e.pitch;
  roll += e.roll;
  canonize();
  return( *this );
}

axe_euler_angles &axe_euler_angles::operator-=( const axe_euler_angles& e ) {
  yaw -= e.yaw;
  pitch -= e.pitch;
  roll -= e.roll;
  canonize();
  return( *this );
}

bool axe_euler_angles::operator==( const axe_euler_angles& e ) const
{
  return( yaw == e.yaw && pitch == e.pitch && yaw == e.yaw );
}

bool axe_euler_angles::operator!=( const axe_euler_angles& e ) const
{
  return( yaw != e.yaw || pitch != e.pitch || yaw != e.yaw );
}

// -----------------------------------------------------------------
// Other methods ---------------------------------------------------
void axe_euler_angles::set_identity() {
  yaw = pitch = roll = 0.0f;
}

bool axe_euler_angles::is_identity() const
{
  return( yaw == 0.0f && pitch == 0.0f && yaw == 0.0f );
}

void axe_euler_angles::canonize() {

  // wrap pitch
  pitch = axmt_wrap_pi( pitch );

  // check limits (-pi/2 ... pi/2)
  if( pitch < -HALF_PI ) {
    pitch = -PI - pitch;
    yaw += PI;
    roll += PI;
  } else if( pitch > HALF_PI ) {
    pitch = PI - pitch;
    yaw += PI;
    roll += PI;
  }

  // check gimbal lock case
  if( fabsf(pitch) > (HALF_PI - 0.00001f) ) {

    // we are in gimbal
    yaw += roll;
    roll = 0.0f;
  } else {

    // not in gimbal
    roll = axmt_wrap_pi( roll );
  }

  yaw = axmt_wrap_pi( yaw );
}

void axe_euler_angles::rotate( axe_vector3& v ) const
{
  v.x += cosf( yaw ) + cosf( pitch ) + cosf( roll );
  v.y += sinf( pitch );
  v.z += sinf( yaw ) + sinf( roll );
}

/* $Id: axmt_angle.cpp,v 1.2 2004/08/31 07:45:20 doneval Exp $ */
