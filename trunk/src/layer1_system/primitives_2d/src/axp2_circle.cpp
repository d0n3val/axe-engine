/**
* @file
* 2D circle code
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      29 Aug 2004
*/
#include "axp2_stdafx.h"

/*$1- Info about this primitive ----------------------------------------------*/
float axe_circle::get_area() const
{
  return( PI * (radius * radius) );
}

/*$1- Create this primitive from another one ---------------------------------*/
axe_circle &axe_circle::create( const axe_vector2& center, const float& radius )
{
  this->center = center;
  this->radius = radius;
  return( *this );
}

axe_circle &axe_circle::create( const axe_circle& circle )
{
  center = circle.center;
  radius = circle.radius;
  return( *this );
}

/*$1- Intersection test with another primitives ------------------------------*/
int axe_circle::intersect( const axe_vector2& point ) const
{
  if( point.distance_pow2_to(center) > (radius * radius) )
  {
    return( AXE_FALSE );
  }

  return( AXE_TRUE );
}

int axe_circle::intersect( const axe_circle& circle ) const
{
  if( circle.center.distance_pow2_to(center) > (radius * radius) + (circle.radius * circle.radius) )
  {
    return( AXE_FALSE );
  }

  return( AXE_TRUE );
}

int axe_circle::intersect( const axe_aa_rectangle& rectangle ) const
{
  return( rectangle.intersect(*this) );
}

/*$1- Distance test to another primitives ------------------------------------*/
float axe_circle::get_distance( const axe_circle& circle, const axp2_dist_type distance_type ) const
{
  AXE_ASSERT( 0 && "not implemented" );
  return( -1.0f );
}

/*$1- Transformation methods -------------------------------------------------*/
void axe_circle::transform( const axe_matrix_3x3& matrix )
{
  AXE_ASSERT( 0 && "not implemented" );
}

/* $Id: axp2_circle.cpp,v 1.1 2004/08/29 18:28:45 doneval Exp $ */
