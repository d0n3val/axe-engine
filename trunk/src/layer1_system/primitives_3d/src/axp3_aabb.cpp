/**
* @file
* axe_aabb class code
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      29 Aug 2004
*/

#include "axp3_stdafx.h"

/*$1- Info about this primitive ----------------------------------------------*/
float axe_aabb::get_volume() const
{
  return( 1.0f );
}

/*$1- Create this primitive from another one ---------------------------------*/
axe_aabb &axe_aabb::create( const axe_vector3& center, const axe_vector3& extents ) {
  this->center = center;
  this->extents = extents;
  return( *this );
}

axe_aabb &axe_aabb::create( const axe_aabb& aabb ) {
  center = aabb.center;
  extents = aabb.extents;
  return( *this );
}

axe_aabb &axe_aabb::create_2( const axe_vector3& pmin, const axe_vector3& pmax ) {

  // check if pmin is really the lower value and pmax, the high value
  axe_vector3  min = pmin;
  axe_vector3  max = pmax;

  if( pmin.x > pmax.x || pmin.y > pmax.y || pmin.z > pmax.z ) {
    min.x = __min( pmin.x, pmax.x );
    min.y = __min( pmin.y, pmax.y );
    min.z = __min( pmin.z, pmax.z );

    max.x = __max( pmin.x, pmax.x );
    max.y = __max( pmin.y, pmax.y );
    max.z = __max( pmin.z, pmax.z );
  }

  center = min + ( (max - min) * 0.5f );
  extents = max - center;
  return( *this );
}

axe_aabb &axe_aabb::create( const axe_vector3* vector_list, const unsigned int vector_count ) {
  register unsigned int i;
  axe_vector3          pmin = vector_list[0];
  axe_vector3          pmax = vector_list[0];

  for( i = 1; i < vector_count; ++i ) {
    if( vector_list[i].x < pmin.x ) {
      pmin.x = vector_list[i].x;
    }

    if( vector_list[i].y < pmin.y ) {
      pmin.y = vector_list[i].y;
    }

    if( vector_list[i].z < pmin.z ) {
      pmin.z = vector_list[i].z;
    }

    if( vector_list[i].x > pmax.x ) {
      pmax.x = vector_list[i].x;
    }

    if( vector_list[i].y > pmax.y ) {
      pmax.y = vector_list[i].y;
    }

    if( vector_list[i].z > pmax.z ) {
      pmax.z = vector_list[i].z;
    }
  }

  return( create_2(pmin, pmax) );
}

/*$1- Intersection test with another primitives ------------------------------*/
int axe_aabb::intersect( const axe_vector3& point ) const
{
  axe_vector3  pmin = center - extents;
  axe_vector3  pmax = center + extents;

  if( point.x < pmin.x ) {
    return( AXE_FALSE );
  }

  if( point.x > pmax.x ) {
    return( AXE_FALSE );
  }

  if( point.y < pmin.y ) {
    return( AXE_FALSE );
  }

  if( point.y > pmax.y ) {
    return( AXE_FALSE );
  }

  if( point.z < pmin.z ) {
    return( AXE_FALSE );
  }

  if( point.z > pmax.z ) {
    return( AXE_FALSE );
  }

  return( AXE_TRUE );
}

int axe_aabb::intersect( const axe_aabb& aabb ) const
{
  axe_vector3  pmin1 = center - extents;
  axe_vector3  pmax1 = center + extents;
  axe_vector3  pmin2 = aabb.center - aabb.extents;
  axe_vector3  pmax2 = aabb.center + aabb.extents;

  if( (pmin1.x > pmax2.x) || (pmax1.x < pmin2.x) ) {
    return( AXE_FALSE );
  }

  if( (pmin1.y > pmax2.y) || (pmax1.y < pmin2.y) ) {
    return( AXE_FALSE );
  }

  if( (pmin1.z > pmax2.z) || (pmax1.z < pmin2.z) ) {
    return( AXE_FALSE );
  }

  return( AXE_TRUE );
}

int axe_aabb::intersect( const axe_sphere& sphere ) const
{
  axe_aabb aabb;

  aabb.center = center;
  aabb.extents.x = extents.x + sphere.radius;
  aabb.extents.y = extents.y + sphere.radius;
  aabb.extents.z = extents.z + sphere.radius;

  return( aabb.intersect(sphere.center) );
}

/*$1- Distance test to another primitives ------------------------------------*/

/*$1- Transformation methods -------------------------------------------------*/
axe_aabb &axe_aabb::transform( const axe_matrix_4x4& matrix ) {

  // transform center
  center = center * matrix;

  // Now calculate new extents
  axe_vector3  ex;

  // Now calculate new extents
  axe_vector3  ey;

  // Now calculate new extents
  axe_vector3  ez;

  //(int)ex.x &= 0x7fffffff; == fabs() ?
  ex.x = fabsf( matrix.d00 * extents.x );
  ex.y = fabsf( matrix.d10 * extents.x );
  ex.z = fabsf( matrix.d20 * extents.x );

  ey.x = fabsf( matrix.d01 * extents.y );
  ey.y = fabsf( matrix.d11 * extents.y );
  ey.z = fabsf( matrix.d21 * extents.y );

  ez.x = fabsf( matrix.d02 * extents.z );
  ez.y = fabsf( matrix.d12 * extents.z );
  ez.z = fabsf( matrix.d22 * extents.z );

  extents.x = ex.x + ey.x + ez.x;
  extents.y = ex.y + ey.y + ez.y;
  extents.z = ex.z + ey.z + ez.z;

  // now scale
  matrix.scale( extents );

  return( *this );
}

/* $Id: axp3_aabb.cpp,v 1.1 2004/08/29 18:28:46 doneval Exp $ */