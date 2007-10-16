/**
* @file
* Axe 'string' library PUBLIC include header
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  24/11/2003
*/
#ifndef __AXE_STRING_H__
  #define __AXE_STRING_H__

/*$1-  main definitions for Axe libs -----------------------------------------*/
  #include "axe_defs.h"

/*$1- Lib version ------------------------------------------------------------*/
  #define AXE_STRING_VERSION  1
  #define AXE_STRING_NAME     "STRING"
  #define AXE_STRING_LIBID    'AXST'

/*$1- DLL proper function prefix ---------------------------------------------*/
  #ifdef _USRDLL
    #define AXST_API  __declspec( dllexport )
    #pragma message( "Compiling Axe 'string' library ..." )
  #else
    #define AXST_API  __declspec( dllimport )
    #pragma message( "Using Axe 'string' library ..." )

/*$1-  Automatic .lib link ---------------------------------------------------*/
    #ifndef AXST_NO_AUTOLINK
      #pragma comment( lib, "axe_string.lib" )
    #endif
  #endif

/** @example axst_test.cpp */

/*$1- Internal buffer size to store strings ----------------------------------*/
  #define AXST_DEFAULT_STRING_SIZE  64
  #define AXST_MAX_STRING_SIZE      8192
  #define AXST_NSUBEXP              10

struct regexp;

/**
* Class for simple strings
*/
class AXST_API axe_string
{
  private:
    char*         string;
    unsigned int  max_size;
    unsigned int  size;
    unsigned int  checksum;
    static char   tmp[AXST_MAX_STRING_SIZE];
  public:

    /*$1- constructor / destructor -------------------------------------------*/
    axe_string();
    ~axe_string();

    /*$1- creators -----------------------------------------------------------*/
    axe_string( unsigned int required_space );
    axe_string( const axe_string& str );
    axe_string( const char* format, ... );
    axe_string( unsigned int max_size, const char* format, ... );
    axe_string&   create( const axe_string& str );
    axe_string&   create( const char* format, ... );
    axe_string&   create( unsigned int max_size, const char* format, ... );

    /*$1- util ---------------------------------------------------------------*/
    void          destroy();
    void          update();
    void          clear();
    void          reserve( const unsigned int required_space );
    unsigned int  get_reserved() const;
    void          cut( unsigned int start, unsigned int end );
    unsigned int  sub_string( unsigned int start, unsigned int end, char* buffer ) const;
    unsigned int  sub_string( unsigned int start, unsigned int end, axe_string& buffer ) const;
    axe_string&   to_upper_case();
    axe_string&   to_lower_case();
    axe_string&   capitalize();
    axe_string&   capitalize_after_underscores();
    axe_string&   trim( int left = true, int right = true, char ch = ' ' );
    axe_string&   delete_char( char ch );
    unsigned int  find_char( char ch, int from_last = false );
    unsigned int  count_char( char ch );
    int           get_token( const char* separator, unsigned int num_token, axe_string& buffer ) const;

    /*$1- Fast util ----------------------------------------------------------*/
    inline unsigned int get_checksum() const
    {
      return( checksum );
    }

    inline int is_empty() const
    {
      return( size == 0 );
    }

    inline unsigned int length() const
    {
      return( size );
    }

    inline char* get_str()
    {
      return( string );
    }

    inline const char* get_str() const
    {
      return( string );
    }

    inline char get_char( int pos )
    {
      return( string[pos] );
    }

    inline char get_char( int pos ) const
    {
      return( string[pos] );
    }

    /*$1- operators ----------------------------------------------------------*/
    axe_string &operator                =( const axe_string& str );
    axe_string &operator                =( const char* str );

    axe_string operator                 +( const axe_string& str ) const;
    axe_string operator                 +( const char* str ) const;

    friend AXST_API axe_string operator +( const char* str1, const axe_string& str2 );

    axe_string &operator                +=( const axe_string& str );
    axe_string &operator                +=( const char* str );
    axe_string &operator                +=( const char ch );

    int operator                        ==( const axe_string& str ) const;
    int operator                        ==( const char* str ) const;

    int operator                        !=( const axe_string& str ) const;
    int operator                        !=( const char* str ) const;

    const char operator [] (int index) const;
    char *operator  [] (int index);

    /*$1- Other concats ------------------------------------------------------*/
    axe_string&   add( const char* format, ... );
    axe_string&   prepend( const char* format, ... );

    /*$1- cast operators -----------------------------------------------------*/
    inline operator const char*  () const
    {
      return( string );
    }

    inline operator char*  ()
    {
      return( string );
    }

    /*$1- special comparisions -----------------------------------------------*/
    int compare_no_case( const axe_string& str ) const;
    int compare_no_case( const char* str ) const;

    /*$1- Regular expressions result -----------------------------------------*/
    struct regex_result
    {
      int size;
      int start[AXST_NSUBEXP];
      int end[AXST_NSUBEXP];
      int len[AXST_NSUBEXP];

      regex_result()
      {
        memset( this, 0, sizeof(axe_string::regex_result) );
      }
    };

    /*$1- Regular expressions ------------------------------------------------*/
    int regex( const char *expr, unsigned int offset = 0, axe_string::regex_result * result = NULL ) const;
    int regex_replace( const char *expr,
                       const char *sub_string,
                       unsigned int offset = 0,
                       axe_string::regex_result * result = NULL );
    int regex_replaceII( const char*     expr,
                         const char*     sub_string,
                         unsigned int    offset = 0,
                         unsigned int*   pIntNextReplace = NULL );
    int replace( const char* word_to_replace, const char* format, ... );
    int replaceII( const char* word_to_replace, const char* format, ... );

    /*$1- Load / Save --------------------------------------------------------*/
    size_t  load( const char* mem, size_t max_size );
    size_t  save( char* mem, size_t max_size ) const;
  private:

    /*$1- internal utils -----------------------------------------------------*/
    void  check_size( const unsigned int required_space );
    void  alloc();
    void  calc_checksum();
    void  reset();
    void  convert_regex_result( regexp * r, axe_string::regex_result * result, unsigned int offset ) const;
};
#endif // __AXE_STRING_H__

/* $Id: axe_string.h,v 1.3 2004/09/20 21:28:08 doneval Exp $ */
