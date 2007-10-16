/**
* @file
* axe_angle class code without optimizations (only FPU here)
*/
#include "axmt_stdafx.h"

/**
* Angle class. Angle 0 point to north (vector2(0,1)) to the right +PI to the left -PI
*/
union AXMT_API  axe_angle
{
  float radians;

  /*$1- Creators -------------------------------------------------------------*/
  axe_angle&  create_deg( const float& degrees );
  axe_angle&  create( const axe_vector2i& vector2 );
  axe_angle&  create( const axe_vector2& vector2 );

  /*$1- Cast -----------------------------------------------------------------*/
  operator  axe_vector2i() const;
  operator  axe_vector2() const;
  operator  axe_vector3() const;
  operator  axe_vector4() const;

  /*$1- Math operations ------------------------------------------------------*/
  axe_angle operator  -() const;

  axe_angle operator  +( const axe_angle& angle ) const;
  axe_angle operator  -( const axe_angle& angle ) const;

  axe_angle operator* ( const float& a ) const;
  axe_angle operator/( const float& a ) const;

  axe_angle &operator+=( const axe_angle& angle );
  axe_angle &operator-=( const axe_angle& angle );

  axe_angle &operator/=( const float& a );
  axe_angle &operator*=( const float& a );

  bool operator==( const axe_angle& angle ) const;
  bool operator!=( const axe_angle& angle ) const;

  bool operator < (const axe_angle& angle) const;
  bool operator >( const axe_angle& angle ) const;
  bool operator >=( const axe_angle& angle ) const;
  bool operator <=( const axe_angle& angle ) const;

  /*$1- Others ---------------------------------------------------------------*/
  void        zero();
  float       get_deg() const;
  axe_angle   get_left_perpendicular() const;
  axe_angle   get_right_perpendicular() const;
  axe_angle   get_opposite() const;
  int         is_between(const axe_angle& angle1, const axe_angle& angle2) const;

  axe_angle   distance_to( const axe_angle& angle ) const;        /// angular distance
};
/* $Id: axmt_angle.h,v 1.2 2004/08/31 07:45:20 doneval Exp $ */
