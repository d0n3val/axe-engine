/**
* @file
* Create / destroy game window
*/
#include "axwd_stdafx.h"

/**
 * Creates the game window
 */
AXWD_API int axwd_start_application( HINSTANCE instance ) {

  /*$1- app already started --------------------------------------------------*/
  AXE_CHECK_DBG_ERROR( (AXE_TRUE != state.started), 9 );

  /*$1- save instance --------------------------------------------------------*/
  state.instance = instance;

  WNDCLASSEX  wcex;

  wcex.cbSize = sizeof( WNDCLASSEX );
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = ( WNDPROC ) wndproc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = state.instance;
  wcex.hbrBackground = NULL;
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = state.application_name;

  wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
  wcex.hIconSm = LoadIcon( wcex.hInstance, (LPCTSTR) 108 );

  /*$1- Load app icon --------------------------------------------------------*/
  if( state.ico_file[0] != 0 ) {
    wcex.hIcon = ( HICON ) LoadImage( state.instance, state.ico_file, IMAGE_ICON, 32, 32, LR_LOADFROMFILE );
  } else {
    wcex.hIcon = LoadIcon( state.instance, (LPCTSTR) 107 );
  }

  /*$1- Load app small icon --------------------------------------------------*/
  if( state.small_ico_file[0] != 0 ) {
    wcex.hIconSm = ( HICON ) LoadImage( state.instance, state.small_ico_file, IMAGE_ICON, 32, 32, LR_LOADFROMFILE );
  } else {
    wcex.hIconSm = LoadIcon( state.instance, (LPCTSTR) 108 );
  }

  /*$1- Load app cursor ------------------------------------------------------*/
  if( state.cursor_file[0] != 0 ) {
    wcex.hCursor = ( HCURSOR ) LoadImage( state.instance, state.cursor_file, IMAGE_ICON, 32, 32, LR_LOADFROMFILE );
  } else {
    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
  }

  /*$1- Register the class ---------------------------------------------------*/
  int result = RegisterClassEx( &wcex );
  AXE_CHECK_DBG_ERROR( (0 != result), 10 );

  /*$1- Set style if user did not provided with one --------------------------*/
  if( state.window_style == 0 ) {
    if( state.fullscreen == AXE_TRUE ) {
      state.window_style = state.fullscreen_style;
      state.window_style_ex = state.fullscreen_style_ex;
    } else {
      state.window_style = state.windowed_style;
      state.window_style_ex = state.windowed_style_ex;
    }
  }

  /*$1- save current resolution ----------------------------------------------*/
  get_current_resolution( state.windowed_resolution_width, state.windowed_resolution_height );

  /*$1- check if user provided window size -----------------------------------*/
  if( state.window_rectangle.right > 0 && state.window_rectangle.bottom > 0 ) {

    /*$1- save required fullscreen resolution --------------------------------*/
    state.fullscreen_resolution_width = state.window_rectangle.right;
    state.fullscreen_resolution_height = state.window_rectangle.bottom;
  } else {

    /*$1- if not specified, we will use current resolution -------------------*/
    state.fullscreen_resolution_width = state.windowed_resolution_width;
    state.fullscreen_resolution_height = state.windowed_resolution_height;
  }

  if( state.fullscreen == AXE_TRUE ) {

    /*$1- change to fullscreen mode. This may need to change screen resolutio */
    if( change_resolution(state.fullscreen_resolution_width, state.fullscreen_resolution_height, AXE_TRUE) != AXE_TRUE ) {
      return( AXE_FALSE );
    }

    state.window_rectangle.right = state.fullscreen_resolution_width;
    state.window_rectangle.bottom = state.fullscreen_resolution_height;
  } else {

    /*$1- in windowed mode, use less than the entire screen ------------------*/
    state.window_rectangle.top = 100;
    state.window_rectangle.left = 100;
    state.window_rectangle.right = state.windowed_resolution_width - 100;
    state.window_rectangle.bottom = state.windowed_resolution_height - 100;
  }

  /*$1- create a rectangle for the new window --------------------------------*/
  RECT  win = state.window_rectangle;

  /*$1- adjust the window to exactly what was requested ----------------------*/
  BOOL  res = AdjustWindowRect( &win, state.window_style, false );
  AXE_CHECK_DBG_ERROR( (false != res), 11 );

  /* In default state, we hide cursor in fullscreen mode */
  if( state.hide_mouse == AXE_TRUE ) {
    ShowCursor( FALSE );
  }

  /*
	 * Set a hook on the WIN32 API to intercept exactly the moment of the window
	 * creation
	 */
  state.window_creation_hook = SetWindowsHookEx( WH_CBT, window_creation_hook, 0, GetCurrentThreadId() );
  AXE_CHECK_DBG_ERROR( (0 != state.window_creation_hook), 12 );

  /*$1- Ok, finally create the window ----------------------------------------*/
  state.window = CreateWindowEx(
      state.window_style_ex,
      state.application_name,
      state.window_name,
      state.window_style,
      win.left,
      win.top,
      win.right - win.left,
      win.bottom - win.top,
      GetDesktopWindow(),
      NULL,
      state.instance,
      NULL );

  /*$1- check ----------------------------------------------------------------*/
  AXE_CHECK_DBG_ERROR( (NULL != state.window), 13 );

  /*$1- Check for errors while creating the window ---------------------------*/
  if( state.exiting == AXE_TRUE ) {
    return( AXE_FALSE );
  }

  /*$1- show the window ------------------------------------------------------*/
  ShowWindow( state.window, SW_SHOW );
  UpdateWindow( state.window );

  int     main_accelerator_resource = 113;
  HACCEL  keyb_ccel = LoadAccelerators( NULL, MAKEINTRESOURCE(main_accelerator_resource) );

  /*$1- Main Loop ------------------------------------------------------------*/
  bool  msg_exist;
  MSG   msg;  //< Messages are saved here
  msg.message = WM_NULL;
  PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );

  do
  {

    /*$1- Lookup for WIN messages --------------------------------------------*/
    if( state.paused == AXE_FALSE ) {
      msg_exist = ( PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0 );
    } else {
      msg_exist = ( GetMessage(&msg, NULL, 0U, 0U) != 0 );
    }

    if( msg_exist == true ) {
      if( keyb_ccel == NULL || state.window == NULL || TranslateAccelerator(state.window, keyb_ccel, &msg) == 0 ) {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
      }

      continue;
    }

    if( state.device_lost == AXE_TRUE ) {
      Sleep( 100 );
    }

    if( state.paused == AXE_FALSE ) {
      if( NULL == state.on_loop || state.on_loop() == AXE_FALSE ) {
        state.exiting = AXE_TRUE;
      }
    }
  } while( state.exiting == AXE_FALSE );

  /*$1- Main Loop ------------------------------------------------------------*/
  if( keyb_ccel != NULL ) {
    DestroyAcceleratorTable( keyb_ccel );
  }

  /*$1- call user function on_end() ------------------------------------------*/
  if( state.on_end != NULL ) {
    state.on_end();
  }

  /*$1- all ok ---------------------------------------------------------------*/
  return( (int) msg.wParam );
}

/**
* Resets the game window to a new configuration
*/
AXWD_API int axwd_reset_application( void ) {
  return( AXE_TRUE );
}

/**
* Pauses the entire app
*/
AXWD_API int axwd_pause_application( void ) {
  state.set_pause( true );
  return( AXE_TRUE );
}

/**
* Unpauses the application
*/
AXWD_API int axwd_resume_application( void ) {
  state.set_pause( false );
  return( AXE_TRUE );
}

/**
* Destroy game window
*/
AXWD_API int axwd_end_application( void ) {

  /*$1- app did not start ----------------------------------------------------*/
  AXE_CHECK_DBG_ERROR( (AXE_TRUE == state.started), 14 );

  /*$1- Destroy the window ---------------------------------------------------*/
  if( state.window != NULL ) {
    DestroyWindow( state.window );
  }

  /*$1- Free memory asociated with device context ----------------------------*/
  if( state.device_context != NULL ) {
    ReleaseDC( state.window, state.device_context );
  }

  /*$1- Unregister window class ----------------------------------------------*/
  UnregisterClass( state.application_name, state.instance );

  /*$1- we didn't check for error, closing anyway ----------------------------*/
  return( AXE_TRUE );
}

/* $Id: axwd_application.cpp,v 1.2 2004/09/20 21:28:10 doneval Exp $ */
