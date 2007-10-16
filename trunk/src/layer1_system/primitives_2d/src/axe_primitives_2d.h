/**
* @file
* Axe 'primitives 2d' library PUBLIC include header
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version  1.0
* @date		  21/12/2004
*/
#ifndef __AXE_PRIMITIVES_2D_H__
  #define __AXE_PRIMITIVES_2D_H__

/*$1-  main definitions for Axe libs -----------------------------------------*/
  #include "axe_defs.h"

/*$1-  Lib version  ----------------------------------------------------------*/
  #define AXE_PRIMITIVES_2D_VERSION  1
  #define AXE_PRIMITIVES_2D_NAME     "PRIMITIVES 2D"
  #define AXE_PRIMITIVES_2D_LIBID    'AXP2'

/*$1-  DLL proper function prefix  -------------------------------------------*/
  #ifdef _USRDLL
    #define AXMT_API  __declspec( dllexport )
    #pragma message( "Compiling Axe 'primitives 2d' library ..." )
  #else
    #define AXMT_API  __declspec( dllimport )
    #pragma message( "Using Axe 'primitives 2d' library ..." )

/*$1-   Automatic .lib lin ---------------------------------------------------*/
    #ifndef AXMT_NO_AUTOLINK
      #pragma comment( lib, "axe_primitives_2d.lib" )
    #endif
  #endif

/*$1- Enum of distance types -------------------------------------------------*/
enum axp2_dist_type
{
  AXP2_DISTANCE_NONE    = 0,
  AXP2_DISTANCE_MIN,
  AXP2_DISTANCE_CENTERS,
  AXP2_DISTANCE_MAX,
  AXP2_DISTANCE_NUM
};

/*$1-  Back declarations, This lib are an exception, and uses C++ classes ----*/
struct axe_circle;
struct axe_aa_rectangle;

/**
* axe_circle class
* To manage 2D circles
*/
struct axe_circle
{
  axe_vector2 center;
  float       radius;

  /*$1- Info about this primitive --------------------------------------------*/
  float get_area() const;

  /*$1- Create this primitive from another one -------------------------------*/
  axe_circle&   create( const axe_vector2& position, const float& radius );
  axe_circle&   create( const axe_circle& circle );

  /*$1- Intersection test with another primitives ----------------------------*/
  int intersect( const axe_vector2& point ) const;
  int intersect( const axe_circle& circle ) const;
  int intersect( const axe_aa_rectangle& rectangle ) const;

  /*$1- Distance test to another primitives ----------------------------------*/
  float get_distance( const axe_circle& circle, const axp2_dist_type distance_type ) const;

  /*$1- Transformation methods -----------------------------------------------*/
  void  transform( const axe_matrix_3x3& matrix );
};

/**
* axe_rectangle class
* To manage 2D axis aligned rectangles
*/
struct axe_aa_rectangle
{
  axe_vector2 center;
  axe_vector2 size;

  /*$1- Info about this primitive --------------------------------------------*/
  float       get_area() const;
  axe_vector2 get_min_point() const;
  axe_vector2 get_max_point() const;

  /*$1- Create this primitive from another one -------------------------------*/
  axe_aa_rectangle&   create( const axe_vector2& center, const axe_vector2& size );
  axe_aa_rectangle&   create_2( const axe_vector2& min_point, const axe_vector2& max_point );
  axe_aa_rectangle&   create( const axe_aa_rectangle& rectangle );

  /*$1- Intersection test with another primitives ----------------------------*/
  int intersect( const axe_vector2& point ) const;
  int intersect( const axe_aa_rectangle& rectangle ) const;
  int intersect( const axe_circle& circle ) const;

  /*$1- Distance test to another primitives ----------------------------------*/
  float get_distance( const axe_aa_rectangle& rectangle, const axp2_dist_type distance_type ) const;

  /*$1- Transformation methods -----------------------------------------------*/
  void  transform( const axe_matrix_3x3& matrix );
};
#endif // __AXE_PRIMITIVES_2D_H__

/* $Id: axe_primitives_2d.h,v 1.1 2004/08/29 18:28:45 doneval Exp $ */
