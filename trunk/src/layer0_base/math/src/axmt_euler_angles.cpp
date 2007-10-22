/**
* @file
* axe_euler_angles class code without optimizations (only FU here)
*/
#include "axmt_stdafx.h"

// -----------------------------------------------------------------
// Creators --------------------------------------------------------
axe_euler_angles &axe_euler_angles::create( const float& _yaw, const float& _pitch, const float& _roll )
{
  yaw = _yaw;
  pitch = _pitch;
  roll = _roll;
  return( *this );
}

axe_euler_angles &axe_euler_angles::create( const axe_euler_angles& e )
{
  yaw = e.yaw;
  pitch = e.pitch;
  roll = e.roll;
  return( *this );
}

// -----------------------------------------------------------------
// Cast operators --------------------------------------------------
axe_euler_angles::operator axe_matrix_3x3() const
{
  axe_matrix_3x3  t;

  float           sin_yaw = sinf( yaw );
  float           cos_yaw = cosf( yaw );

  float           sin_pitch = sinf( pitch );
  float           cos_pitch = cosf( pitch );

  float           sin_roll = sinf( roll );
  float           cos_roll = cosf( roll );

  t.d00 = cos_yaw * cos_roll + sin_yaw * sin_pitch * sin_roll;
  t.d01 = ( -cos_yaw ) * sin_roll + sin_yaw * sin_pitch * cos_roll;
  t.d02 = sin_yaw * cos_pitch;

  t.d10 = sin_roll * cos_pitch;
  t.d11 = cos_roll * cos_pitch;
  t.d12 = ( -sin_pitch );

  t.d20 = ( -sin_yaw ) * cos_roll + cos_yaw * sin_pitch * sin_roll;
  t.d21 = sin_roll * sin_yaw + cos_yaw * sin_pitch * cos_roll;
  t.d22 = cos_yaw * cos_pitch;

  return( t );
}

axe_euler_angles::operator axe_matrix_4x3() const
{
  axe_matrix_3x3  t3;
  axe_matrix_4x3  t4;

  return( t4 = t3 = *this );
}

axe_euler_angles::operator axe_matrix_4x4() const
{
  axe_matrix_3x3  t3;
  axe_matrix_4x4  t4;

  return( t4 = t3 = *this );
}

axe_euler_angles::operator axe_quaternion() const
{
  axe_quaternion  t;

  float           sin_yaw = sinf( yaw * 0.5f );
  float           cos_yaw = cosf( yaw * 0.5f );

  float           sin_pitch = sinf( pitch * 0.5f );
  float           cos_pitch = cosf( pitch * 0.5f );

  float           sin_roll = sinf( roll * 0.5f );
  float           cos_roll = cosf( roll * 0.5f );

  t.w = cos_yaw * cos_pitch * cos_roll + sin_yaw * sin_pitch * sin_roll;
  t.x = -cos_yaw * sin_pitch * cos_roll + sin_yaw * cos_pitch * sin_roll;
  t.y = cos_yaw * sin_pitch * sin_roll + sin_yaw * cos_pitch * cos_roll;
  t.z = sin_yaw * sin_pitch * cos_roll + cos_yaw * cos_pitch * sin_roll;

  return( t );
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

axe_euler_angles &axe_euler_angles::operator+=( const axe_euler_angles& e )
{
  yaw += e.yaw;
  pitch += e.pitch;
  roll += e.roll;
  canonize();
  return( *this );
}

axe_euler_angles &axe_euler_angles::operator-=( const axe_euler_angles& e )
{
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
void axe_euler_angles::set_identity()
{
  yaw = pitch = roll = 0.0f;
}

bool axe_euler_angles::is_identity() const
{
  return( yaw == 0.0f && pitch == 0.0f && yaw == 0.0f );
}

void axe_euler_angles::canonize()
{
  // wrap pitch
  pitch = axe_angle( pitch );

  // check limits (-pi/2 ... pi/2)
  if( pitch < -HALF_PI )
  {
    pitch = -PI - pitch;
    yaw += PI;
    roll += PI;
  }
  else if( pitch > HALF_PI )
  {
    pitch = PI - pitch;
    yaw += PI;
    roll += PI;
  }

  // check gimbal lock case
  if( fabsf(pitch) > (HALF_PI - 0.00001f) )
  {
    // we are in gimbal
    yaw += roll;
    roll = 0.0f;
  }
  else
  {
    // not in gimbal
    roll = axe_angle( roll );
  }

  yaw = axe_angle( yaw );
}

void axe_euler_angles::rotate( axe_vector3& v ) const
{
  v.x += cosf( yaw ) + cosf( pitch ) + cosf( roll );
  v.y += sinf( pitch );
  v.z += sinf( yaw ) + sinf( roll );
}

/* $Id: axmt_euler_angles.cpp,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
