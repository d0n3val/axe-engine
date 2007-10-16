/**
* @file
* Manages events for the game window
*/
#include "axwd_stdafx.h"

/**
* SetDCPixelFormat.
* Select the pixel format for the context.
*/
int set_device_pixel_format(HDC device_context, BYTE color_depth )
{
  int                           pixel_format;
  static PIXELFORMATDESCRIPTOR  pfd;

  pfd.nSize = sizeof( PIXELFORMATDESCRIPTOR );
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = color_depth;
  pfd.cRedBits = 0;
  pfd.cRedShift = 0;
  pfd.cGreenBits = 0;
  pfd.cGreenShift = 0;
  pfd.cBlueBits = 0;
  pfd.cBlueShift = 0;
  pfd.cAlphaBits = 0;
  pfd.cAlphaShift = 0;
  pfd.cAccumBits = 0;
  pfd.cAccumRedBits = 0;
  pfd.cAccumGreenBits = 0;
  pfd.cAccumBlueBits = 0;
  pfd.cAccumAlphaBits = 0;
  pfd.cDepthBits = color_depth;
  pfd.cStencilBits = 0;
  pfd.cAuxBuffers = 0;
  pfd.iLayerType = PFD_MAIN_PLANE;
  pfd.bReserved = 0;
  pfd.dwLayerMask = 0;
  pfd.dwVisibleMask = 0;
  pfd.dwDamageMask = 0;

  //! Choose the best pixel format
  pixel_format = ChoosePixelFormat( device_context, &pfd );
  AXE_CHECK_ERROR( (pixel_format != FALSE), 20 );

  //! Apply this pixel format
  bool b = AXE_TO_BOOL( SetPixelFormat(device_context, pixel_format, &pfd) );
  AXE_CHECK_ERROR( (b!= FALSE), 20 );

  //! all ok
  return( AXE_TRUE );
}

/**
* Events manager
*/
LRESULT CALLBACK wndproc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
  //PAINTSTRUCT    ps;			//< Paint struct
  switch( message )
  {
    // Pass these messages to user defined functions
    //HANDLE_MSG(hWnd, WM_CREATE, on_create);

    /*$1- Window creation ------------------------------------------------------*/
    case WM_CREATE:
      {
        // Get device context
        state.device_context = GetDC( hWnd );
        if( NULL == state.device_context )
        {
          state.exiting = AXE_TRUE;
        }

        AXE_CHECK_ERROR( (NULL != state.device_context), 19 );

        //! Set pixel format
        set_device_pixel_format(state.device_context, state.color_depth);

        // save window size
        update_window_rectangle();

        // save state
        state.started = AXE_TRUE;

        // call user function on_start...()
        if( state.on_start != NULL )
        {
          if( AXE_FALSE == state.on_start() )
          {
            state.exiting = AXE_TRUE;
          }
        }
      }

      break;

    /*$1- we get/lost the focus ------------------------------------------------*/
    case WM_ACTIVATE:
      if( wParam == WA_INACTIVE )
      {
        if( state.fullscreen == AXE_TRUE )
        {
          state.set_pause( true );
        }

        if( state.on_focus != NULL )
        {
          state.on_focus( AXE_FALSE );
        }
      }
      else
      {
        if( state.fullscreen == AXE_TRUE )
        {
          state.set_pause( false );
        }

        if( state.on_focus != NULL )
        {
          state.on_focus( AXE_TRUE );
        }
      }

      break;

    /*$1- Halt if the user is resizing the window ------------------------------*/
    case WM_ENTERSIZEMOVE:
      state.set_pause( true );
      break;

    /*$1- Left paused mode when finished resizing the window -------------------*/
    case WM_EXITSIZEMOVE:
      state.set_pause( false );

      // manage resize
      update_window_rectangle();
      call_resize_callback();
      break;

    /*$1- windows notifys a change in our screen size --------------------------*/
    case WM_SIZE:
      switch( wParam )
      {
        case SIZE_MAXIMIZED:
          state.set_pause( false );
          state.maximized = AXE_TRUE;
          state.minimized = AXE_FALSE;

          // manage resize
          if( state.ignore_resize == AXE_FALSE )
          {
            update_window_rectangle();
            call_resize_callback();
          }

          break;

        case SIZE_MINIMIZED:
          state.set_pause( true );
          state.maximized = AXE_FALSE;
          state.minimized = AXE_TRUE;
          break;

        case SIZE_RESTORED:
          state.set_pause( false );
          if( state.maximized == AXE_TRUE || state.minimized == AXE_TRUE )
          {
            // manage resize
            if( state.ignore_resize == AXE_FALSE )
            {
              update_window_rectangle();
              call_resize_callback();
            }
          }
          else
          {
            // wait for resizing end
          }

          state.maximized = AXE_FALSE;
          state.minimized = AXE_FALSE;
          break;
      }

      break;

    /*$1- manage mouse cursor --------------------------------------------------*/
    case WM_SETCURSOR:
      if( state.paused == AXE_TRUE )
      {
        return( 1 );
      }

      // Turn off Windows cursor in fullscreen mode
      if( state.hide_mouse == AXE_TRUE )
      {
        ShowCursor( FALSE );
      }
      else
      {
        ShowCursor( TRUE );
      }

      return( 1 );  // prevent Windows from setting cursor to window class cursor
      break;

    /*$1- Fix the minimum window that user can resize --------------------------*/
    case WM_GETMINMAXINFO:
      ( (MINMAXINFO*) lParam )->ptMinTrackSize.x = 100;
      ( (MINMAXINFO*) lParam )->ptMinTrackSize.y = 100;
      break;

    /*$1- manage system commands -----------------------------------------------*/
    case WM_SYSCOMMAND:
      switch( wParam )
      {

        /*$1- disable screensaver ------------------------------------------------*/
        case SC_SCREENSAVE:
          return( 1 );

        /*$1- disable other features not compatible with fullscreen --------------*/
        case SC_MOVE:
        case SC_SIZE:
        case SC_MAXIMIZE:
        case SC_KEYMENU:
        case SC_MONITORPOWER:
          if( state.fullscreen == AXE_TRUE )
          {
            return( 1 );
          }

          break;
      }

      break;

    /*$1- APM events -----------------------------------------------------------*/
    case WM_POWERBROADCAST:
      switch( wParam )
      {

        /*$1-  APM enters suspend mode -------------------------------------------*/
        case 0x0000:
          if( state.on_suspend != NULL )
          {
            state.on_suspend();
          }

          return( 1 );

        /*$1- APM resumes suspend mode -------------------------------------------*/
        case 0x0007:
          if( state.on_resume != NULL )
          {
            state.on_resume();
          }

          return( 1 );
      }

      break;

    /*$1- System ask us to paint -----------------------------------------------*/
    case WM_PAINT:
      // Handle paint messages when the app is paused
      if( state.fullscreen == AXE_FALSE && state.paused == AXE_TRUE && state.on_repaint != NULL )
      {
        state.on_repaint();
      }

      break;

    /*$1- Keyboard event -------------------------------------------------------*/
    case WM_CHAR:
      if( state.on_key != NULL )
      {
        state.on_key( (char) wParam );
      }

      break;

    /*$1- Manage mouse enter / exits client window -----------------------------*/
    case WM_NCHITTEST:
      {
        if( state.fullscreen == AXE_TRUE )
        {
          return( 1 );
        }

        LRESULT result;
        result = DefWindowProc( hWnd, message, wParam, lParam );
        if( result == 1 && state.mouse_in_window == AXE_FALSE )
        {
          // the mouse just entered in the client area
          state.mouse_in_window = AXE_TRUE;
          if( state.on_mouse_in_window != NULL )
          {
            POINT p;
            p.x = (int) LOWORD( lParam );
            p.y = (int) HIWORD( lParam );

            ScreenToClient( state.window, &p );
            state.on_mouse_in_window( AXE_TRUE, p.x, p.y );
          }
        }

        if( result != 1 && state.mouse_in_window == AXE_TRUE )
        {
          // the cursor is in the non-client area
          state.mouse_in_window = AXE_FALSE;
          if( state.on_mouse_in_window != NULL )
          {
            state.on_mouse_in_window( AXE_FALSE, 0, 0 );
          }

          ShowCursor( TRUE );
        }

        return( result );
      }

      break;

    // manage close/destroy
    case WM_DESTROY:
    case WM_CLOSE:
    case WM_QUIT:
      state.exiting = AXE_TRUE;
      return( 1 );
  }

  //! No managed event
  return( DefWindowProc(hWnd, message, wParam, lParam) );
}

/**
* Window creation hook callback function
*/
LRESULT CALLBACK window_creation_hook( int hook_code, WPARAM wParam, LPARAM lParam )
{
  if( hook_code == HCBT_CREATEWND )
  {
    // Connect the new window with the class instance
    /*HWND hWnd = (HWND)wParam;
		CBT_CREATEWND *cw = (CBT_CREATEWND*)lParam;

		if(wndCreator) {
		SetWindowLong(hWnd, GWL_USERDATA, (LONG)wndCreator);
		}*/
    // save main window pointer
    state.window = ( HWND ) wParam;

    // Unregister the hook procedure
    if( state.window_creation_hook != NULL )
    {
      UnhookWindowsHookEx( state.window_creation_hook );
      state.window_creation_hook = NULL;
    }

    // Return 0 to allow continued creation
    return( 0 );
  }

  return( CallNextHookEx(state.window_creation_hook, hook_code, wParam, lParam) );
}

/* $Id: axwd_wndproc.cpp,v 1.1 2004/06/09 18:23:59 doneval Exp $ */
