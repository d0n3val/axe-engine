/**
* @file
* Axe 'primitives 3d' library PUBLIC include header
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version  1.0
* @date		  29/12/2004
*/
#ifndef __AXE_PRIMITIVES_3D_H__
  #define __AXE_PRIMITIVES_3D_H__

/*$1-  main definitions for Axe libs -----------------------------------------*/
  #include "axe_defs.h"

/*$1-  Lib version  ----------------------------------------------------------*/
  #define AXE_PRIMITIVES_3D_VERSION 1
  #define AXE_PRIMITIVES_3D_NAME    "PRIMITIVES 3D"
  #define AXE_PRIMITIVES_3D_LIBID   'AXP3'

/*$1-  DLL proper function prefix  -------------------------------------------*/
  #ifdef _USRDLL
    #define AXMT_API  __declspec( dllexport )
    #pragma message( "Compiling Axe 'primitives 3d' library ..." )
  #else
    #define AXMT_API  __declspec( dllimport )
    #pragma message( "Using Axe 'primitives 3d' library ..." )

/*$1-   Automatic .lib lin ---------------------------------------------------*/
    #ifndef AXMT_NO_AUTOLINK
      #pragma comment( lib, "axe_primitives_3d.lib" )
    #endif
  #endif

/*$1- Enum of distance types -------------------------------------------------*/
enum axp3_dist_type
{
  AXP2_DISTANCE_NONE    = 0,
  AXP2_DISTANCE_MIN,
  AXP2_DISTANCE_CENTERS,
  AXP2_DISTANCE_MAX,
  AXP2_DISTANCE_NUM
};

/*$1-  Back declarations, This lib are an exception, and uses C++ classes ----*/
struct axe_sphere;
struct axe_aabb;

/**
* axe_sphere class
* To manage spheres
*/
struct axe_sphere
{
  axe_vector3  center;
  float         radius;

  /*$1- Info about this primitive --------------------------------------------*/
  float get_volume() const;

  /*$1- Create this primitive from another one -------------------------------*/
  axe_sphere&   create( const axe_vector3& position, const float& radius );
  axe_sphere&   create( const axe_sphere& sphere );
  axe_sphere&   create( const axe_vector3* vector_list, const unsigned int vector_count );

  /*$1- Intersection test with another primitives ----------------------------*/
  int intersect( const axe_vector3& point ) const;
  int intersect( const axe_sphere& sphere ) const;
  int intersect( const axe_aabb& aabb ) const;

  /*$1- Distance test to another primitives ----------------------------------*/

  /*$1- Transformation methods -----------------------------------------------*/
  axe_sphere&   transform( const axe_matrix_4x4& matrix );
};

/**
* axe_aabb class
* To manage Axis Aligned Bounding Boxes
*/
struct axe_aabb
{
  axe_vector3  center, extents;

  /*$1- Info about this primitive --------------------------------------------*/
  float get_volume() const;

  /*$1- Create this primitive from another one -------------------------------*/
  axe_aabb&   create( const axe_vector3& position, const axe_vector3& extents );
  axe_aabb&   create( const axe_aabb& aabb );
  axe_aabb&   create_2( const axe_vector3& pmin, const axe_vector3& pmax );
  axe_aabb&   create( const axe_vector3* vector_list, const unsigned int vector_count );

  /*$1- Intersection test with another primitives ----------------------------*/
  int intersect( const axe_vector3& point ) const;
  int intersect( const axe_aabb& aabb ) const;
  int intersect( const axe_sphere& sphere ) const;

  /*$1- Distance test to another primitives ----------------------------------*/

  /*$1- Transformation methods -----------------------------------------------*/
  axe_aabb&   transform( const axe_matrix_4x4& matrix );
};
#endif // __AXE_PRIMITIVES_3D_H__

/* $Id: axe_primitives_3d.h,v 1.1 2004/08/29 18:28:46 doneval Exp $ */
