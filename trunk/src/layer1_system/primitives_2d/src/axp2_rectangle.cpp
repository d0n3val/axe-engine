/**
* @file
* 2D axis aligned rectangle code
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      25 Jul 2004
*/
#include "axp2_stdafx.h"

/*$1- Info about this primitive ----------------------------------------------*/
float axe_aa_rectangle::get_area() const
{
  return( size.x * size.y );
}

axe_vector2 axe_aa_rectangle::get_min_point() const
{
  axe_vector2 pmin;

  return( pmin.create(center.x - size.x, center.y - size.y) );
}

axe_vector2 axe_aa_rectangle::get_max_point() const
{
  axe_vector2 pmax;

  return( pmax.create(center.x + size.x, center.y + size.y) );
}

/*$1- Create this primitive from another one ---------------------------------*/
axe_aa_rectangle &axe_aa_rectangle::create( const axe_vector2& center, const axe_vector2& size )
{
  this->center = center;
  this->size = size;
  return( *this );
}

axe_aa_rectangle &axe_aa_rectangle::create_2( const axe_vector2& min_point, const axe_vector2& max_point )
{
  center.x =  ((max_point.x - min_point.x) * 0.5f) + min_point.x;
  center.y =  ((max_point.y - min_point.y) * 0.5f ) + min_point.y;
  size.create( max_point.x - max_point.x, max_point.y - max_point.y );
  return( *this );
}

axe_aa_rectangle &axe_aa_rectangle::create( const axe_aa_rectangle& rectangle )
{
  center = rectangle.center;
  size = rectangle.size;
  return( *this );
}

/*$1- Intersection test with another primitives ------------------------------*/
int axe_aa_rectangle::intersect( const axe_vector2& point ) const
{
  axe_vector2i  pmin = get_min_point();
  axe_vector2i  pmax = get_max_point();

  if( point.x < pmin.x )
  {
    return( AXE_FALSE );
  }

  if( point.x > pmax.x )
  {
    return( AXE_FALSE );
  }

  if( point.y < pmin.y )
  {
    return( AXE_FALSE );
  }

  if( point.y > pmax.y )
  {
    return( AXE_FALSE );
  }

  return( AXE_TRUE );
}

int axe_aa_rectangle::intersect( const axe_aa_rectangle& rectangle ) const
{
  if( (center.x - size.x) > (rectangle.center.x + rectangle.size.x) )
  {
    return( AXE_FALSE );
  }

  if( (center.x + size.x) < (rectangle.center.x - rectangle.size.x) )
  {
    return( AXE_FALSE );
  }

  if( (center.y - size.y) > (rectangle.center.y + rectangle.size.y) )
  {
    return( AXE_FALSE );
  }

  if( (center.y + size.y) < (rectangle.center.y - rectangle.size.y) )
  {
    return( AXE_FALSE );
  }

  return( AXE_TRUE );
}

int axe_aa_rectangle::intersect( const axe_circle& circle ) const
{
  axe_aa_rectangle  r( *this );

  r.size.x += circle.radius;
  r.size.y += circle.radius;

  return( r.intersect(circle.center) );
}

/*$1- Distance test to another primitives ------------------------------------*/
float axe_aa_rectangle::get_distance( const axe_aa_rectangle& rectangle, const axp2_dist_type distance_type ) const
{
  AXE_ASSERT( 0 && "not implemented" );
  return( -1.0f );
}

/*$1- Transformation methods -------------------------------------------------*/
void axe_aa_rectangle::transform( const axe_matrix_3x3& matrix )
{
  AXE_ASSERT( 0 && "not implemented" );
}

/* $Id: axp2_rectangle.cpp,v 1.1 2004/08/29 18:28:45 doneval Exp $ */
