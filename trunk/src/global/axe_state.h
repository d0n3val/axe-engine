/**
* @file
* Pure base class for all libraries states
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @version   1.0
* @date      12 Apr 2004
*/
#ifndef __AXE_STATE_H__
  #define __AXE_STATE_H__

  #define LIB_NAME_LONG 64

/**
* Generic lib state
*/
class         axe_state
{
  public:
    unsigned int  last_error;               /// last error code
    unsigned int  debug_mode;               /// indicates debug or release compilation mode
    unsigned int  lib_id;                   /// ID of the library (FLI)
    char          lib_name[LIB_NAME_LONG];  /// Name if the library
    unsigned int  lib_version;
    void ( *error_callback ) (int, const char*, long);
  public:
    axe_state()
    {
      last_error = 0;
      lib_id = 0;
      lib_name[0] = 0;
      lib_version = 0;
      error_callback = NULL;
  #ifdef _DEBUG
      debug_mode = AXE_TRUE;
  #else
      debug_mode = AXE_FALSE;
  #endif
    }

    void set_error( int num, const char* file, long line )
    {
      last_error = num;
      if( error_callback != NULL )
      {
        ( *error_callback ) ( num, file, line );
      }
    }

    virtual~axe_state()
    {
    };
};
#endif // __AXE_STATE_H__

/* $Id: axe_state.h,v 1.1 2004/05/02 16:32:30 doneval Exp $ */
