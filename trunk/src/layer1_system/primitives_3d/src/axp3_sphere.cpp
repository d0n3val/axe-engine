/**
* @file
* axe_sphere class code
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      29 Aug 2004
*/

#include "axp3_stdafx.h"

/*$1- Info about this primitive ----------------------------------------------*/
float axe_sphere::get_volume() const
{
  return( 1.0f );
}

/*$1- Create this primitive from another one ---------------------------------*/
axe_sphere &axe_sphere::create( const axe_vector3& center, const float& radius )
{
  this->center = center;
  this->radius = radius;
  return( *this );
}

axe_sphere &axe_sphere::create( const axe_sphere& sphere )
{
  center = sphere.center;
  radius = sphere.radius;
  return( *this );
}

/// we use Ritter method at http://www.graphicsgems.org
axe_sphere &axe_sphere::create( const axe_vector3* vector_list, const unsigned int vector_count )
{
  register unsigned int i;

  // First, find the max/min vector for each axis
  axe_vector3          min[3];
  axe_vector3          max[3];

  min[0].x = min[1].y = min[2].z = -INFINITY;
  max[0].x = max[1].y = max[2].z = INFINITY;

  for( i = 1; i < vector_count; ++i )
  {
    if( vector_list[i].x < min[0].x )
    {
      min[0] = vector_list[i];
    }

    if( vector_list[i].y < min[1].y )
    {
      min[1] = vector_list[i];
    }

    if( vector_list[i].z < min[2].z )
    {
      min[2] = vector_list[i];
    }

    if( vector_list[i].x > max[0].x )
    {
      max[0] = vector_list[i];
    }

    if( vector_list[i].y > max[1].y )
    {
      max[1] = vector_list[i];
    }

    if( vector_list[i].z > max[2].z )
    {
      max[2] = vector_list[i];
    }
  }

  // ok, now find the pair of vectors with largest distance between them
  axe_vector3  pmin;
  axe_vector3  pmax;
  float         distance = 0.0f;

  for( i = 0; i < 3; ++i )
  {
    if( min[i].distance_man_to(max[0]) > distance )
    {
      pmin = min[i];
      pmax = max[0];
      distance = min[i].distance_man_to( max[0] );
    }

    if( min[i].distance_man_to(max[1]) > distance )
    {
      pmin = min[i];
      pmax = max[1];
      distance = min[i].distance_man_to( max[1] );
    }

    if( min[i].distance_man_to(max[2]) > distance )
    {
      pmin = min[i];
      pmax = max[2];
      distance = min[i].distance_man_to( max[2] );
    }
  }

  // Now form an sphere from this pair
  axe_sphere  sphere;
  sphere.center = pmin + ( (pmax - pmin) * 0.5f );
  sphere.radius = pmin.distance_to( sphere.center );

  // Now loop all vertices and adjust center and radius
  for( i = 0; i < vector_count; ++i )
  {
    if( sphere.intersect(vector_list[i]) == AXE_FALSE )
    {
      float d = vector_list[i].distance_to( sphere.center ) * 0.5f;
      float r = sphere.radius * 0.5f;

      sphere.center.x += ( d - r );
      sphere.center.y += ( d - r );
      sphere.center.z += ( d - r );

      sphere.radius = d + r;
    }
  }

  return( *this );
}

/*$1- Intersection test with another primitives ------------------------------*/
int axe_sphere::intersect( const axe_vector3& point ) const
{
  if( point.distance_pow2_to(center) > (radius * radius) )
  {
    return( AXE_FALSE );
  }

  return( AXE_TRUE );
}

int axe_sphere::intersect( const axe_sphere& sphere ) const
{
  if( sphere.center.distance_pow2_to(center) > (radius * radius) + (sphere.radius * sphere.radius) )
  {
    return( AXE_FALSE );
  }

  return( AXE_TRUE );
}

int axe_sphere::intersect( const axe_aabb& aabb ) const
{
  return( aabb.intersect(*this) );
}

/*$1- Distance test to another primitives ------------------------------------*/

/*$1- Transformation methods -------------------------------------------------*/
axe_sphere &axe_sphere::transform( const axe_matrix_4x4& matrix )
{
  // transform center
  center = center * matrix;

  // now scale radius
  axe_vector3  radius_vector = center;
  center.x += radius;

  matrix.scale( radius_vector );

  radius = radius_vector.module();
  return( *this );
}

/* $Id: axp3_sphere.cpp,v 1.1 2004/08/29 18:28:46 doneval Exp $ */
