/**
* @file
* Definition of the AXE assert macro and function
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @version   1.0
* @date      11 Apr 2004
*/
#ifndef __AXE_ASSERT_H__
  #define __AXE_ASSERT_H__

/*$1- Assert only in debug ---------------------------------------------------*/
  #ifdef _DEBUG
    #pragma warning( disable : 4505 )
    #pragma warning( disable : 4127 )

/**
* _axe_assert is called if we are in _DEBUG. It returns 1 if user weants to break
*/
static int _axe_assert( const char*         expr,
                        const char*         msg,
                        const char*         file,
                        const char*         func,
                        const unsigned long line )
{
  static char   _assert_msg[4096];
  static char   _assert_title[MAX_PATH];
  static DWORD  _lastErr = GetLastError();
  static char*  _file = NULL;
  static int    r = 1;
  static void*  _last_error_msg = NULL;

  /*$1- Cut to show only filename (no dirs) ----------------------------------*/
  _file = (char *) strrchr( file, '\\' );
  _file = _file ? _file + 1 : (char*) file;

  /*$1- If lastError exists, create a description message --------------------*/
  if( _lastErr != 0 )
  {
    FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL,
      _lastErr,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),  // Default language
      (LPTSTR) & _last_error_msg,
      0,
      NULL );
  }

  /*$1- Create a message suitable for the Output Debug  ----------------------*/
  _snprintf_s( _assert_msg, 4096, 2000, "%s(%u) : ASSERT (%s)\n", _file, line, expr );

  if( NULL != msg )
  {
    //strcat( _assert_msg, " Message: " );
    strncat_s( _assert_msg, 4096, msg, 1000 );
  }

  if( NULL != _last_error_msg ) {
    strcat_s( _assert_msg, 4096, "GetLastError(): " );
    strncat_s( _assert_msg, 4096, (const char*) _last_error_msg, 1000 );
  }
  OutputDebugString( _assert_msg );

  /*$1- Paste it to clipboard ------------------------------------------------*/
  if( OpenClipboard(NULL) )
  {
    HGLOBAL hMem;
    char*   pMem;

    hMem = GlobalAlloc( GHND | GMEM_DDESHARE, strlen(_assert_msg) + 1 );

    if( hMem )
    {
      pMem = (char*) GlobalLock( hMem );
      strcpy_s( pMem, strlen(_assert_msg) + 1, _assert_msg );
      GlobalUnlock( hMem );

      EmptyClipboard();
      SetClipboardData( CF_TEXT, hMem );
    }

    CloseClipboard();
    GlobalFree( hMem );
  }

  /*$1- Now a message for the MessageBox Title -------------------------------*/
  char  modulePath[MAX_PATH];
  GetModuleFileName( NULL, modulePath, MAX_PATH );

  const char*   moduleName = strrchr( modulePath, '\\' );
  moduleName = moduleName ? moduleName + 1 : modulePath;

  char  title[MAX_PATH + 20];
  sprintf_s( title, MAX_PATH + 20, "AXE ASSERT (%s)", moduleName );

  /*$1- Message box contents -------------------------------------------------*/
  _snprintf_s( _assert_msg, 4096, 2000, "%s(%u) : %s()\n\nExpr: (%s)", _file, line, func, expr );

  if( NULL != msg )
  {
    strcat_s( _assert_msg, 4096, "\n\nMessage:\n" );
    strncat_s( _assert_msg, 4096, msg, 1000 );
  }

  /*
  if( NULL != _last_error_msg ) {
    strcat( _assert_msg, "\n\nlast_error(): " );
    strncat( _assert_msg, (const char*) _last_error_msg, 1000 );
  }
*/
  int res = MessageBox( NULL, _assert_msg, title, MB_ICONERROR | MB_TASKMODAL | MB_YESNOCANCEL );
  if( IDYES == res )
  {
    r = 0;
  }
  else if( IDCANCEL == res )
  {
    _exit( EXIT_FAILURE );
  }

  /*$1- R --------------------------------------------------------------------*/
  if( NULL != _last_error_msg )
  {
    LocalFree( _last_error_msg );
  }

  SetLastError( _lastErr );
  return( r );
}

/*$1- Assert macro -----------------------------------------------------------*/
    #define AXE_ASSERT( expr )                                              \
  do                                                                        \
  {                                                                         \
    if( !(expr) )                                                           \
    {                                                                       \
      if( _axe_assert(#expr, NULL, __FILE__, __FUNCTION__, __LINE__) == 0 ) \
      {                                                                     \
        _asm                                                                \
        {                                                                   \
          int 3                                                             \
        }                                                                   \
      }                                                                     \
    }                                                                       \
  } while( 0 )

/*$1- Assert macro with message ----------------------------------------------*/
    #define AXE_ASSERT_MSG( expr, msg )                                    \
  do                                                                       \
  {                                                                        \
    if( !(expr) )                                                          \
    {                                                                      \
      if( _axe_assert(#expr, msg, __FILE__, __FUNCTION__, __LINE__) == 0 ) \
      {                                                                    \
        _asm                                                               \
        {                                                                  \
          int 3                                                            \
        }                                                                  \
      }                                                                    \
    }                                                                      \
  } while( 0 )
  #else // _DEBUG
    #define AXE_ASSERT( expr )          __noop
    #define AXE_ASSERT_MSG( expr, msg ) __noop
  #endif
#endif // __AXE_ASSERT_H__

    /* $Id: axe_assert.h,v 1.3 2004/10/19 23:10:59 doneval Exp $ */
    