/**
* @file
* Axe 'script' library PUBLIC include header
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  19 Dec 2004
*/
#ifndef __AXE_SCRIPT_H__
  #define __AXE_SCRIPT_H__

/*$1- Main definitions for Axe libs ------------------------------------------*/
  #include "axe_defs.h"

/*$1- DLL proper function prefix ---------------------------------------------*/
  #ifdef _USRDLL
    #define AXSC_API  extern "C"__declspec( dllexport )
    #pragma message( "Compiling Axe 'Script' ..." )
  #else
    #define AXSC_API  extern "C"__declspec( dllimport )
    #pragma message( "Using Axe 'Script' ..." )

/*$1- Automatic .lib link ----------------------------------------------------*/
    #ifndef AXSC_NO_AUTOLINK
      #pragma comment( lib, "axe_script.lib" )
    #endif
  #endif

/*$1- Default stack size for script execution --------------------------------*/
  #define AXSC_DEFAULT_STACK_SIZE 1000

/*$1- Possible execution results ---------------------------------------------*/
enum axsc_execution
{
  AXSC_EXECUTION_ERROR    = 0,
  AXSC_EXECUTION_FINISHED,
  AXSC_EXECUTION_SUSPENDED,
  AXSC_EXECUTION_ABORTED,
  AXSC_EXECUTION_EXCEPTION
};

/*$1- Possible method types --------------------------------------------------*/
enum axsc_method_type
{
  AXSC_METHOD_NORMAL      = -1,
  AXSC_METHOD_CONSTRUCTOR,
  AXSC_METHOD_DESTRUCTOR,
  AXSC_METHOD_ASSIGNMENT,
  AXSC_METHOD_ADD_ASSIGN,
  AXSC_METHOD_SUB_ASSIGN,
  AXSC_METHOD_MUL_ASSIGN,
  AXSC_METHOD_DIV_ASSIGN,
  AXSC_METHOD_MOD_ASSIGN,
  AXSC_METHOD_OR_ASSIGN,
  AXSC_METHOD_AND_ASSIGN,
  AXSC_METHOD_XOR_ASSIGN,
  AXSC_METHOD_SLL_ASSIGN,
  AXSC_METHOD_SRL_ASSIGN,
  AXSC_METHOD_LAST_ASSIGN,
  AXSC_METHOD_ADD,
  AXSC_METHOD_SUB,
  AXSC_METHOD_MUL,
  AXSC_METHOD_DIV,
  AXSC_METHOD_MOD,
  AXSC_METHOD_EQUAL,
  AXSC_METHOD_NOTEQUAL,
  AXSC_METHOD_LESSTHAN,
  AXSC_METHOD_GREATERTHAN,
  AXSC_METHOD_LEQUAL,
  AXSC_METHOD_GEQUAL,
  AXSC_METHOD_LOGIC_OR,
  AXSC_METHOD_LOGIC_AND,
  AXSC_METHOD_BIT_OR,
  AXSC_METHOD_BIT_AND,
  AXSC_METHOD_BIT_XOR,
  AXSC_METHOD_BIT_SLL,
  AXSC_METHOD_BIT_SRL,
  AXSC_METHOD_LAST_DUAL,
  AXSC_METHOD_INDEX,
  AXSC_METHOD_NEGATE,
  AXSC_METHOD_COUNT
};

/*$1- States for this lib ----------------------------------------------------*/
enum axsc_states
{
  AXSC_VERSION            = 1,
  AXSC_LIBRARY_NAME,
  AXSC_LIBRARY_ID,
  AXSC_DEBUG_MODE,
  AXSC_LAST_ERROR,
  AXSC_STATE_COUNT,
};

/*$1- Callback macros --------------------------------------------------------*/
  #define AXSC_FUNCTION( function )         asFUNCTION( function )
  #define AXSC_METHOD( class_name, method ) asMETHOD( class_name, method )
  #define AXSC_PROPERTY( name, prop )       ( size_t ) & ( ((name*) 0)->prop )

/** @example axsc_test.cpp */
extern "C"
{
  union asUPtr;

  /*$1- axsc_script.cpp ------------------------------------------------------*/
  AXSC_API unsigned int axsc_get( const int query_state );
  AXSC_API unsigned int axsc_set( const int query_state, const unsigned int new_value );
  AXSC_API const char*  axsc_get_error_message( const unsigned int error_number );
  AXSC_API int          axsc_set_error_callback( void (*error_callback) (int, const char*, long) );

  /*$1- axsc_init.cpp --------------------------------------------------------*/
  AXSC_API int  axsc_init();
  AXSC_API int  axsc_done();

  /*$1- axsc_register.cpp  ---------------------------------------------------*/
  AXSC_API int  axsc_register_variable( const char* declaration, void* address );
  AXSC_API int  axsc_register_function( const char* declaration, asUPtr function );
  AXSC_API int  axsc_register_string_factory( const char* data_type, asUPtr function );

  /*$1- axsc_register_class.cpp ----------------------------------------------*/
  AXSC_API int  axsc_begin_register_class( const char* name, size_t size, bool type = false );
  AXSC_API int  axsc_register_property( const char* declaration, int offset );
  AXSC_API int  axsc_register_method( const char*       declaration,
                                      asUPtr            method,
                                      axsc_method_type  type = AXSC_METHOD_NORMAL );
  AXSC_API int  axsc_end_register_class();

  /*$1- axsc_load_file.cpp ---------------------------------------------------*/
  AXSC_API int  axsc_load_file( const char* file_name );

  /*$1- axsc_compile.cpp -----------------------------------------------------*/
  AXSC_API int  axsc_compile();

  /*$1- axsc_call_function.cpp -----------------------------------------------*/
  AXSC_API int            axsc_begin_call_function( const char* function_name );
  AXSC_API int            axsc_add_argument( void* argument, size_t sizeof_argument );
  AXSC_API int            axsc_set_return_value( void* return_value, size_t sizeof_return_value );
  AXSC_API axsc_execution axsc_end_call_function();
} // extern "C"

/*$1-  -----------------------------------------------------------------------*/

/*$1-  -----------------------------------------------------------------------*/

/*$1-  -----------------------------------------------------------------------*/
//-----------------------------------------------------------------
// Function pointers
  #include <memory.h>

typedef void ( *asFUNCTION_t ) ();

class asCUnknownClass;
typedef void ( asCUnknownClass:: *asMETHOD_t ) ();

union asUPtr
{
  asFUNCTION_t  func;
  asMETHOD_t    mthd;
};

  #define asFUNCTION( f )           asFunctionPtr( (void(*) ()) (f) )
  #define asFUNCTIONP( f, p )       asFunctionPtr( (void(*) ()) ((void(*) p) (f)) )
  #define asFUNCTIONPR( f, p, r )   asFunctionPtr( (void(*) ()) ((r(*) p) (f)) )
  #define asMETHOD( c, m )          asSMethodPtr < sizeof( void(c:: *) () ) >::Convert( (void(c:: *) ()) (&c::m) )
  #define asMETHODP( c, m, p )      asSMethodPtr < sizeof( void(c:: *) () ) >::Convert( (void(c:: *) p) (&c::m) )
  #define asMETHODPR( c, m, p, r )  asSMethodPtr < sizeof( void(c:: *) () ) >::Convert( (r(c:: *) p) (&c::m) )

inline asUPtr asFunctionPtr( asFUNCTION_t func )
{
  asUPtr  p;
  memset( &p, 0, sizeof(p) );
  p.func = func;

  return( p );
}

// Method pointers

// Declare a dummy class so that we can determine the size of a simple method pointer
class asCSimpleDummy
{
};
const int SINGLE_PTR_SIZE = sizeof( void(asCSimpleDummy:: *) () );

// Define template
template<int N>
struct asSMethodPtr
{
  template<class M>
  static asUPtr Convert( M Mthd )
  {
    int ERROR_UnsupportedMethodPtr[-1];
    return( 0 );
  }
};

// Template specialization
template<>
struct asSMethodPtr < SINGLE_PTR_SIZE >
{
  template<class M>
  static asUPtr Convert( M Mthd )
  {
    asUPtr  p;
    memset( &p, 0, sizeof(p) );

    memcpy( &p, &Mthd, SINGLE_PTR_SIZE );

    return( p );
  }
};

  #if defined( _MSC_VER ) && !defined( __MWERKS__ )

// MSVC and Intel uses different sizes for different class method pointers
template<>
struct asSMethodPtr < SINGLE_PTR_SIZE + 1 * sizeof( int ) >
{
  template<class M>
  static asUPtr Convert( M Mthd )
  {
    asUPtr  p;
    memset( &p, 0, sizeof(p) );

    memcpy( &p, &Mthd, SINGLE_PTR_SIZE + sizeof(int) );

    return( p );
  }
};

template<>
struct asSMethodPtr < SINGLE_PTR_SIZE + 2 * sizeof( int ) >
{
  template<class M>
  static asUPtr Convert( M Mthd )
  {
    // This is where a class with virtual inheritance falls
    // Since method pointers of this type doesn't have all the
    // information we need we force a compile failure for this case.
    int     ERROR_VirtualInheritanceIsNotAllowedForMSVC[-1];

    // The missing information is the location of the vbase table,
    // which is only known at compile time.
    // You can get around this by forward declaring the class and
    // storing the sizeof its method pointer in a constant. Example:
    // class ClassWithVirtualInheritance;
    // const int ClassWithVirtualInheritance_workaround = sizeof(void ClassWithVirtualInheritance::*());
    // This will force the compiler to use the unknown type
    // for the class, which falls under the next case
    asUPtr  p;
    return( p );
  }
};

template<>
struct asSMethodPtr < SINGLE_PTR_SIZE + 3 * sizeof( int ) >
{
  template<class M>
  static asUPtr Convert( M Mthd )
  {
    asUPtr  p;
    memset( &p, 0, sizeof(p) );

    memcpy( &p, &Mthd, SINGLE_PTR_SIZE + 3 * sizeof(int) );

    return( p );
  }
};
  #endif

/*$1--------------------------------------------------------------------------*/

/*$1-  -----------------------------------------------------------------------*/

/*$1-  -----------------------------------------------------------------------*/
#endif // __AXE_SCRIPT_H__

/* $Id: axe_script.h,v 1.5 2004/09/20 21:28:13 doneval Exp $ */
