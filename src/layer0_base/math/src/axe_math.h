/**
* @file
* Axe 'math' library PUBLIC include header
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version  1.0
* @date		  04/12/2003
*/
#ifndef __AXE_MATH_H__
  #define __AXE_MATH_H__

/*$1- Cast to DX9 structs ----------------------------------------------------*/
  #include <d3dx9math.h>

  #pragma warning( disable : 4201 )
  #pragma warning( disable : 4324 )

/*$1-  main definitions for Axe libs -----------------------------------------*/
  #include "axe_defs.h"

/*$1-  Lib version  ----------------------------------------------------------*/
  #define AXE_MATH_VERSION  1
  #define AXE_MATH_NAME     "MATH"
  #define AXE_MATH_LIBID    'AXMT'

/*$1-  DLL proper function prefix  -------------------------------------------*/
  #ifdef _USRDLL
    #define AXMT_API  __declspec( dllexport )
    #pragma message( "Compiling Axe 'math' library ..." )
  #else
    #define AXMT_API  __declspec( dllimport )
    #pragma message( "Using Axe 'math' library ..." )

/*$1-   Automatic .lib lin ---------------------------------------------------*/
    #ifndef AXMT_NO_AUTOLINK
      #pragma comment( lib, "axe_math.lib" )
    #endif
  #endif

/*$1-  SSE / 3dnow / 3dnow! data types  --------------------------------------*/
  #ifndef _USRDLL
typedef struct __declspec ( intrin_type )
__declspec( align(16) )
__m128
{
  float m128_f32[4];
} __m128; /// SSE register
typedef struct __declspec ( intrin_type )
__declspec( align(16) )
__m64
{
  float m64_f32[2];
} __m64;  /// 3dnow register
  #endif

/** @example axmt_test.cpp */
/*
int axmt_signi(int)
int axmt_signd(double)
int axmt_signf(float)

int axmt_sin()
int axmt_cos()
int axmt_tan()

int axmt_asin()
int axmt_acos()
int axmt_atan()

//friend AXMT_API axe_vector2 operator + (const float &a, const axe_vector2 &u);

MAX
MIN

int absi(int)
float absf(float)
double absd(double)

int floori(int)
float floorf(float)
double floord(double)

*/
enum axmt_side
{
  AXMT_INVALID= 0,
  AXMT_FRONT,
  AXMT_BEHIND,
  AXMT_LEFT,
  AXMT_RIGHT,
  AXMT_COUNT
};

/*$1- Useful math constants --------------------------------------------------*/
static const float  EPSILON = 0.0001f;
static const float  INFINITY = 3.4e38f;
static const float  PI = 3.14159265358979323846f;
static const float  TWO_PI = 6.28318530717958647692f;
static const float  QUAD_PI = 9.86960440108935861883f;
static const float  HALF_PI = 1.57079632679489661923f;
static const float  QUARTER_PI = 0.78539816339744830961f;
static const float  INV_PI = 0.31830988618379067154f;
static const float  INV_TWO_PI = 0.15915494309189533576f;
static const float  DEG_TO_RAD = 0.01745329251994329577f;
static const float  RAD_TO_DEG = 57.2957795130823208768f;

/*$1-  This uses C++ classes -------------------------------------------------*/
struct axe_float;
struct axe_angle;
union axe_vector2i;
union axe_vector2;
union axe_vector3;
union axe_vector4;
union axe_euler_angles;
union axe_matrix_3x3;
union axe_matrix_4x3;
union axe_matrix_4x4;
union axe_quaternion;

/**
* Simplify float operations
* @check axmt_float.cpp
*/
struct AXMT_API axe_float
{
  float f;

  /*$1- Creators -------------------------------------------------------------*/
  axe_float (const float&f);

  /*$1- Cast -----------------------------------------------------------------*/
  operator int() const;
  operator float() const;

  /*$1- Math operations ------------------------------------------------------*/
  bool operator ==( const axe_float& v ) const;
  bool operator !=( const axe_float& v ) const;
  bool operator >=( const axe_float& v ) const;
  bool operator <=( const axe_float& v ) const;

  /*$1- Others ---------------------------------------------------------------*/
  axe_float set_infinity();
  axe_float inverse() const;
  axe_float sin() const;
  axe_float cos() const;
  axe_float tan() const;
  axe_float asin() const;
  axe_float acos() const;
  axe_float atan() const;
  axe_float floor() const;
  axe_float set_max( axe_float& v );
  axe_float set_min( axe_float& v );
  axe_float cap( axe_float& min, axe_float& max );
};

/**
* Angle class: 0 Rad is (1,0) +pi/2 is (0,1) -pi/s is (0,-1) and +-pi is (-1,0)
*/
struct AXMT_API axe_angle
{
  axe_float radians;

  /*$1- Creators -------------------------------------------------------------*/
  axe_angle (const float&rad);
  axe_angle (const axe_angle&ang);
  axe_angle&  create_deg( const float& degrees );
  axe_angle&  create( const axe_vector2i& vector2 );
  axe_angle&  create( const axe_vector2& vector2 );

  /*$1- Cast -----------------------------------------------------------------*/
  operator float() const;
  operator axe_vector2i() const;
  operator axe_vector2() const;
  operator axe_vector3() const;
  operator axe_vector4() const;

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

  bool operator < (const axe_angle&angle) const;
  bool operator >( const axe_angle& angle ) const;
  bool operator >=( const axe_angle& angle ) const;
  bool operator <=( const axe_angle& angle ) const;

  /*$1- Others ---------------------------------------------------------------*/
  void      zero();
  void      wrap_pi();
  float     get_deg() const;
  axe_angle get_left_perpendicular() const;
  axe_angle get_right_perpendicular() const;
  axe_angle get_opposite() const;
  int       is_in_front( const axe_angle& angle, float aperture ) const;
  int       is_behind( const axe_angle& angle, float aperture ) const;
  int       is_on_the_left( const axe_angle& angle, float aperture = PI ) const;
  int       is_on_the_right( const axe_angle& angle, float aperture = PI ) const;
  axmt_side find_side( const axe_angle& angle, float aperture ) const;

  // Argument order is important
  int       is_between( const axe_angle& angle1, const axe_angle& angle2 ) const;
  axe_angle distance_to( const axe_angle& angle ) const;
};

/**
* Simple vector 2d (x,y) class but with integer data
* @check axmt_vector2i.cpp
*/
union AXMT_API  axe_vector2i
{
  struct
  {
    int x, y;
  };
  __declspec( align(16) )
  int ptr[2];

  /*$1- Creators -------------------------------------------------------------*/
  axe_vector2i&   create( const int& x, const int& y );
  axe_vector2i&   create( const axe_vector2i& v );

  /*$1- Cast -----------------------------------------------------------------*/
  operator  axe_vector2() const;
  operator  axe_vector3() const;
  operator  axe_vector4() const;

  /*$1- Math operations ------------------------------------------------------*/
  axe_vector2i operator -() const;

  axe_vector2i operator +( const axe_vector2i& v ) const;
  axe_vector2i operator -( const axe_vector2i& v ) const;

  int operator* ( const axe_vector2i& v ) const;  /// dot product
  axe_vector2i operator* ( const int& a ) const;
  axe_vector2i operator/( const int& a ) const;

  axe_vector2i &operator+=( const axe_vector2i& v );
  axe_vector2i &operator-=( const axe_vector2i& v );

  axe_vector2i &operator/=( const int& a );
  axe_vector2i &operator*=( const int& a );

  bool operator==( const axe_vector2i& v ) const;
  bool operator!=( const axe_vector2i& v ) const;

  bool operator < (const axe_vector2i&v) const;
  bool operator >( const axe_vector2i& v ) const;
  bool operator >=( const axe_vector2i& v ) const;
  bool operator <=( const axe_vector2i& v ) const;

  /*$1- Others ---------------------------------------------------------------*/
  void  zero();
  void  negate();
  float module() const;

  float distance_to( const axe_vector2i& v ) const;       /// euclidean distance
  float distance_pow2_to( const axe_vector2i& v ) const;  /// euclidean distance ^2
  int   distance_man_to( const axe_vector2i& v ) const;   /// manhattan distance
};

/**
* Simple vector 2d (x,y) class
* @check axmt_vector2.cpp
*/
union AXMT_API  axe_vector2
{
  struct
  {
    float x, y;
  };

  //__declspec( align(16) )
  float ptr[2];

  /*$1- Creators -------------------------------------------------------------*/
  axe_vector2&  create( const float& x, const float& y );
  axe_vector2&  create( const axe_vector2& v );

  /*$1- Cast -----------------------------------------------------------------*/
  operator  axe_vector2i() const;
  operator  axe_vector3() const;
  operator  axe_vector4() const;
  operator  D3DXVECTOR2() const;
  operator D3DXVECTOR2*  ();
  operator const D3DXVECTOR2*  () const;

  /*$1- Math operations ------------------------------------------------------*/
  axe_vector2 operator  -() const;

  axe_vector2 operator  +( const axe_vector2& v ) const;
  axe_vector2 operator  -( const axe_vector2& v ) const;

  float operator* ( const axe_vector2& v ) const; /// dot product
  axe_vector2 operator* ( const float& a ) const;
  axe_vector2 operator/( const float& a ) const;

  axe_vector2 &operator+=( const axe_vector2& v );
  axe_vector2 &operator-=( const axe_vector2& v );

  axe_vector2 &operator/=( const float& a );
  axe_vector2 &operator*=( const float& a );

  bool operator==( const axe_vector2& v ) const;
  bool operator!=( const axe_vector2& v ) const;

  bool operator < (const axe_vector2&v) const;
  bool operator >( const axe_vector2& v ) const;
  bool operator >=( const axe_vector2& v ) const;
  bool operator <=( const axe_vector2& v ) const;

  /*$1- Others ---------------------------------------------------------------*/
  void        zero();
  void        normalize();
  void        negate();
  float       module() const;
  float       module_approx() const;

  float       distance_to( const axe_vector2& v ) const;        /// euclidean distance
  float       distance_pow2_to( const axe_vector2& v ) const;   /// euclidean distance ^2
  float       distance_approx_to( const axe_vector2& v ) const; /// fast approximate distance
  float       distance_man_to( const axe_vector2& v ) const;    /// manhattan distance
  axe_vector2 lerp( const axe_vector2& v, const float& factor ) const;
};

/**
* Simple vector 3d (x,y,z) class
* @see axmt_vector3.cpp
*/
union AXMT_API  axe_vector3
{
  struct
  {
    float x, y, z;
  };

  //__declspec( align(16) )
  float ptr[3];

  /*$1- Creators -------------------------------------------------------------*/
  axe_vector3&  create( const float& x, const float& y, const float& z );
  axe_vector3&  create( const axe_vector3& v );

  /*$1- Cast -----------------------------------------------------------------*/
  operator  axe_vector2i() const;
  operator  axe_vector2() const;
  operator  axe_vector4() const;
  operator  D3DXVECTOR3() const;
  operator D3DXVECTOR3*  ();
  operator const D3DXVECTOR3*  () const;

  /*$1- Math operations ------------------------------------------------------*/
  axe_vector3 operator  -() const;

  axe_vector3 operator  +( const axe_vector3& v ) const;
  axe_vector3 operator  -( const axe_vector3& v ) const;

  float operator* ( const axe_vector3& v ) const;       /// dot product
  axe_vector3 operator^( const axe_vector3& v ) const;  /// cross product
  axe_vector3 operator* ( const float& a ) const;
  axe_vector3 operator/( const float& a ) const;

  axe_vector3 &operator+=( const axe_vector3& v );
  axe_vector3 &operator-=( const axe_vector3& v );

  axe_vector3 &operator/=( const float& a );
  axe_vector3 &operator*=( const float& a );

  bool operator==( const axe_vector3& v ) const;
  bool operator!=( const axe_vector3& v ) const;

  bool operator < (const axe_vector3&v) const;
  bool operator >( const axe_vector3& v ) const;
  bool operator >=( const axe_vector3& v ) const;
  bool operator <=( const axe_vector3& v ) const;

  /*$1- Others ---------------------------------------------------------------*/
  void        zero();
  void        normalize();
  void        negate();
  float       module() const;
  float       module_approx() const;

  float       distance_to( const axe_vector3& v ) const;        /// euclidean distance
  float       distance_pow2_to( const axe_vector3& v ) const;   /// euclidean distance ^2
  float       distance_approx_to( const axe_vector3& v ) const; /// fast approximate distance
  float       distance_man_to( const axe_vector3& v ) const;    /// manhattan distance
  axe_vector3 lerp( const axe_vector3& v, const float& factor ) const;
};

/**
* Simple vector 3d (x,y,z,w) class
* @see axmt_vector4.cpp
*/
union AXMT_API  axe_vector4
{
  struct
  {
    float x, y, z, w;
  };
  __declspec( align(16) )
  float ptr[4];

  /*$1- Creators -------------------------------------------------------------*/
  axe_vector4&  create( const float& x, const float& y, const float& z, const float& w );
  axe_vector4&  create( const axe_vector4& v );

  /*$1- Cast -----------------------------------------------------------------*/
  operator  axe_vector2i() const;
  operator  axe_vector2() const;
  operator  axe_vector3() const;
  operator  D3DXVECTOR4() const;
  operator D3DXVECTOR4*  ();
  operator const D3DXVECTOR4*  () const;

  /*$1- Math operations ------------------------------------------------------*/
  axe_vector4 operator  -() const;

  axe_vector4 operator  +( const axe_vector4& v ) const;
  axe_vector4 operator  -( const axe_vector4& v ) const;

  float operator* ( const axe_vector4& v ) const; /// dot product
  axe_vector4 operator* ( const float& a ) const;
  axe_vector4 operator/( const float& a ) const;

  axe_vector4 &operator+=( const axe_vector4& v );
  axe_vector4 &operator-=( const axe_vector4& v );

  axe_vector4 &operator/=( const float& a );
  axe_vector4 &operator*=( const float& a );

  bool operator==( const axe_vector4& v ) const;
  bool operator!=( const axe_vector4& v ) const;

  bool operator < (const axe_vector4&v) const;
  bool operator >( const axe_vector4& v ) const;
  bool operator >=( const axe_vector4& v ) const;
  bool operator <=( const axe_vector4& v ) const;

  /*$1- Others ---------------------------------------------------------------*/
  void        zero();
  void        normalize();
  void        negate();
  float       module() const;
  float       module_approx() const;

  float       distance_to( const axe_vector4& v ) const;        /// euclidean distance
  float       distance_pow2_to( const axe_vector4& v ) const;   /// euclidean distance ^2
  float       distance_approx_to( const axe_vector4& v ) const; /// fast approximate distance
  float       distance_man_to( const axe_vector4& v ) const;    /// manhattan distance
  axe_vector4 lerp( const axe_vector4& v, const float& factor ) const;
};

/**
* Euler angles class
* @see axmt_euler_angles.cpp
*/
union AXMT_API  axe_euler_angles
{
  struct
  {
    float yaw, pitch, roll;
  };
  __declspec( align(16) )
  float ptr[3];

  /*$1- Creators -------------------------------------------------------------*/
  axe_euler_angles&   create( const float& yaw, const float& pitch, const float& roll );
  axe_euler_angles&   create( const axe_euler_angles& e );

  /*$1- Cast -----------------------------------------------------------------*/
  operator  axe_matrix_3x3() const;
  operator  axe_matrix_4x3() const;
  operator  axe_matrix_4x4() const;
  operator  axe_quaternion() const;

  /*$1- Math operations ------------------------------------------------------*/
  axe_euler_angles operator   -() const;

  axe_euler_angles operator   +( const axe_euler_angles& e ) const;
  axe_euler_angles operator   -( const axe_euler_angles& e ) const;

  axe_euler_angles &operator  +=( const axe_euler_angles& e );
  axe_euler_angles &operator  -=( const axe_euler_angles& e );

  bool operator               ==( const axe_euler_angles& e ) const;
  bool operator               !=( const axe_euler_angles& e ) const;

  /*$1- Others ---------------------------------------------------------------*/
  void  set_identity();
  bool  is_identity() const;
  void  canonize();
  void  rotate( axe_vector3& v ) const;
};

/**
* Matrix 3 row 3 column class
* @see axmt_matrix_3x3.cpp
*/
union AXMT_API  axe_matrix_3x3
{
  struct
  {
    float d00, d10, d20;
    float d01, d11, d21;
    float d02, d12, d22;
  };
  __declspec( align(16) )
  float ptr[9];

  /*$1- Creators -------------------------------------------------------------*/
  axe_matrix_3x3&   create( const float&  d00,
                            const float&  d10,
                            const float&  d20,
                            const float&  d01,
                            const float&  d11,
                            const float&  d21,
                            const float&  d02,
                            const float&  d12,
                            const float&  d22 );
  axe_matrix_3x3&   create( const axe_vector3& v0, const axe_vector3& v1, const axe_vector3& v2 );
  axe_matrix_3x3&   create( const axe_matrix_3x3& m );
  axe_matrix_3x3&   create_x_rotation( float fAngle );
  axe_matrix_3x3&   create_y_rotation( float fAngle );
  axe_matrix_3x3&   create_z_rotation( float fAngle );

  /*$1- Cast -----------------------------------------------------------------*/
  operator  axe_euler_angles() const;
  operator  axe_matrix_4x3() const;
  operator  axe_matrix_4x4() const;
  operator  axe_quaternion() const;
  operator  D3DXMATRIX() const;

  /*$1- Math operations ------------------------------------------------------*/
  axe_matrix_3x3 operator +( const axe_matrix_3x3& m ) const;
  axe_matrix_3x3 operator -( const axe_matrix_3x3& m ) const;
  axe_matrix_3x3 operator* ( const axe_matrix_3x3& m ) const;

  axe_vector3 operator* ( const axe_vector3& v ) const;
  axe_vector4 operator* ( const axe_vector4& v ) const;
  friend AXMT_API axe_vector3 operator* ( const axe_vector3& v, const axe_matrix_3x3& m );
  friend AXMT_API axe_vector4 operator* ( const axe_vector4& v, const axe_matrix_3x3& m );

  axe_matrix_3x3 &operator+=( const axe_matrix_3x3& m );
  axe_matrix_3x3 &operator-=( const axe_matrix_3x3& m );
  axe_matrix_3x3 operator*=( const axe_matrix_3x3& m );

  bool operator==( const axe_matrix_3x3& m ) const;
  bool operator!=( const axe_matrix_3x3& m ) const;

  /*$1- Others ---------------------------------------------------------------*/
  void              set_identity();
  bool              is_identity() const;

  axe_vector3       get_xcol() const;
  axe_vector3       get_ycol() const;
  axe_vector3       get_zcol() const;

  axe_matrix_3x3&   transpose();
  float             get_determinant() const;
  axe_matrix_3x3&   invert();

  void              scale( axe_vector3& v ) const;
  void              rotate( axe_vector3& v ) const;
};

/**
* Matrix 3 row 4 column class
* @see axmt_matrix_4x3.cpp
*/
union AXMT_API  axe_matrix_4x3
{
  struct
  {
    float d00, d10, d20, d30;
    float d01, d11, d21, d31;
    float d02, d12, d22, d32;
  };
  __declspec( align(16) )
  float ptr[12];

  /*$1- Creators -------------------------------------------------------------*/
  axe_matrix_4x3&   create( const float&  d00,
                            const float&  d10,
                            const float&  d20,
                            const float&  d30,
                            const float&  d01,
                            const float&  d11,
                            const float&  d21,
                            const float&  d31,
                            const float&  d02,
                            const float&  d12,
                            const float&  d22,
                            const float&  d32 );
  axe_matrix_4x3&   create( const axe_vector3&  v0,
                            const axe_vector3&  v1,
                            const axe_vector3&  v2,
                            const axe_vector3&  position );
  axe_matrix_4x3&   create( const axe_matrix_4x3& m );

  /*$1- Cast -----------------------------------------------------------------*/
  operator                axe_euler_angles() const;
  operator                axe_matrix_3x3() const;
  operator                axe_matrix_4x4() const;
  operator                axe_quaternion() const;
  operator                D3DXMATRIX() const;

  // Math operations -------------------*/
  axe_matrix_4x3 operator +( const axe_matrix_4x3& m ) const;
  axe_matrix_4x3 operator -( const axe_matrix_4x3& m ) const;
  axe_matrix_4x3 operator* ( const axe_matrix_4x3& m ) const;

  axe_vector3 operator* ( const axe_vector3& v ) const;
  axe_vector4 operator* ( const axe_vector4& v ) const;
  friend AXMT_API axe_vector3 operator* ( const axe_vector3& v, const axe_matrix_4x3& m );
  friend AXMT_API axe_vector4 operator* ( const axe_vector4& v, const axe_matrix_4x3& m );

  axe_matrix_4x3 &operator+=( const axe_matrix_4x3& m );
  axe_matrix_4x3 &operator-=( const axe_matrix_4x3& m );
  axe_matrix_4x3 operator*=( const axe_matrix_4x3& m );

  bool operator==( const axe_matrix_4x3& m ) const;
  bool operator!=( const axe_matrix_4x3& m ) const;

  // Others ----------------------------*/
  void set_identity();
  bool is_identity() const;

  void set_position( const axe_vector3& v );
  axe_vector3 get_position() const;

  axe_vector3 get_xcol() const;
  axe_vector3 get_ycol() const;
  axe_vector3 get_zcol() const;

  axe_matrix_4x3& transpose();
  float get_determinant() const;
  axe_matrix_4x3& invert();

  void scale( axe_vector3& v ) const;
  void rotate( axe_vector3& v ) const;
  void translate( axe_vector3& v ) const;
};

/**
* Matrix 4 row 4 column class
* @see axmt_matrix_4x4.cpp
*/
union AXMT_API  axe_matrix_4x4
{
  struct
  {
    float d00, d10, d20, d30;
    float d01, d11, d21, d31;
    float d02, d12, d22, d32;
    float d03, d13, d23, d33;
  };
  __declspec( align(16) )
  float ptr[16];

  /*$1- Creators -------------------------------------------------------------*/
  axe_matrix_4x4&   create( const float* values );
  axe_matrix_4x4&   create( const float&  d00,
                            const float&  d10,
                            const float&  d20,
                            const float&  d30,
                            const float&  d01,
                            const float&  d11,
                            const float&  d21,
                            const float&  d31,
                            const float&  d02,
                            const float&  d12,
                            const float&  d22,
                            const float&  d32,
                            const float&  d03,
                            const float&  d13,
                            const float&  d23,
                            const float&  d33 );
  axe_matrix_4x4&   create( const axe_vector3&  v0,
                            const axe_vector3&  v1,
                            const axe_vector3&  v2,
                            const axe_vector3&  position );
  axe_matrix_4x4&   create( const axe_matrix_4x4& m );

  /*$1- Cast -----------------------------------------------------------------*/
  operator float*  ();
  operator const float*  () const;
  operator axe_euler_angles() const;
  operator axe_matrix_3x3() const;
  operator axe_matrix_4x3() const;
  operator axe_quaternion() const;
  operator D3DXMATRIX() const;

  //*$1- Math operations -------------------*/

  axe_matrix_4x4 operator +( const axe_matrix_4x4& m ) const;
  axe_matrix_4x4 operator -( const axe_matrix_4x4& m ) const;
  axe_matrix_4x4 operator* ( const axe_matrix_4x4& m ) const;

  axe_vector3 operator* ( const axe_vector3& v ) const;
  axe_vector4 operator* ( const axe_vector4& v ) const;
  friend AXMT_API axe_vector3 operator* ( const axe_vector3& v, const axe_matrix_4x4& m );
  friend AXMT_API axe_vector4 operator* ( const axe_vector4& v, const axe_matrix_4x4& m );

  axe_matrix_4x4 &operator+=( const axe_matrix_4x4& m );
  axe_matrix_4x4 &operator-=( const axe_matrix_4x4& m );
  axe_matrix_4x4 &operator*=( const axe_matrix_4x4& m );

  bool operator==( const axe_matrix_4x4& m ) const;
  bool operator!=( const axe_matrix_4x4& m ) const;

  /*$1- Others ---------------------------------------------------------------*/
  void              set_identity();
  bool              is_identity() const;

  void              set_position( const axe_vector3& v );
  axe_vector3       get_position() const;

  void              set_xcol( const axe_vector3& v );
  void              set_ycol( const axe_vector3& v );
  void              set_zcol( const axe_vector3& v );
  axe_vector3       get_xcol() const;
  axe_vector3       get_ycol() const;
  axe_vector3       get_zcol() const;

  axe_matrix_4x4&   transpose();
  axe_matrix_4x4&   invert();
  void              set_rotation( const axe_euler_angles& angles );
  float             get_determinant() const;

  void              scale( axe_vector3& v ) const;
  void              rotate( axe_vector3& v ) const;
  void              translate( axe_vector3& v ) const;
  void              transform( axe_vector3& v ) const;
};

/**
* Quaternion class
* @see axmt_quaternion.cpp
*/
union AXMT_API  axe_quaternion
{
  struct
  {
    float w, x, y, z;
  };
  __declspec( align(16) )
  float ptr[4];

  /*$1- Creators -------------------------------------------------------------*/
  axe_quaternion&   create( const float& w, const float& x, const float& y, const float& z );
  axe_quaternion&   create( const axe_quaternion& q );

  /*$1- Cast -----------------------------------------------------------------*/
  operator  axe_euler_angles() const;
  operator  axe_matrix_3x3() const;
  operator  axe_matrix_4x3() const;
  operator  axe_matrix_4x4() const;
  operator  D3DXQUATERNION() const;
  operator D3DXQUATERNION*  ();
  operator const D3DXQUATERNION*  () const;

  /*$1-Math operations -------------------------------------------------------*/
  axe_quaternion operator -() const;
  axe_quaternion operator -( const axe_quaternion& q ) const;

  float operator* ( const axe_quaternion& q ) const;          /// dot product
  axe_quaternion operator^( const axe_quaternion& q ) const;  /// cross product
  axe_quaternion &operator-=( const axe_quaternion& q );
  axe_quaternion &operator^=( const axe_quaternion& q );      /// cross product
  bool operator==( const axe_quaternion& q ) const;
  bool operator!=( const axe_quaternion& q ) const;

  /*$1- Others ---------------------------------------------------------------*/
  void              set_identity();
  bool              is_identity() const;

  axe_quaternion&   normalize();
  axe_quaternion&   conjugate();
  axe_quaternion&   invert();

  axe_quaternion    slerp( const axe_quaternion& q, const float& factor ) const;

  void              rotate( axe_vector3& v ) const;
};
#endif // __AXE_MATH_H__

/* $Id: axe_math.h,v 1.4 2004/09/20 21:28:08 doneval Exp $ */
