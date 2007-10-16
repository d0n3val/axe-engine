/**
* @file
* Control singleton
* @author    Ricard Pillosu <doneval\@users.sf.net>
* @date      18 Sep 2004
*/
#include "axen_control.h"

//#include "axen_events.h"
bool axen_control::           active = false;
axen_control *axen_control::  instance = NULL;

/*$1- Constructor & Destructor -----------------------------------------------*/

/**
* Constructor
*/
axen_control::axen_control()
{
  keyboard_id = mouse_id = -1;
}

/**
* Destructor
*/
axen_control::~axen_control()
{
  active = false;
}

/*$1- Singleton stuff --------------------------------------------------------*/

/**
* Singleton creator
*/
axen_control *axen_control::create()
{
  if( active == false )
  {
    instance = new axen_control;
    active = true;
  }

  return( instance );
}

/*$1- Method -----------------------------------------------------------------*/

/**
* Init
*/
void axen_control::init( HWND window, HINSTANCE instance )
{
  axco_init( window, instance );

  int num_dev = axco_get_device_count();
  for( register int i = 0; i < num_dev; ++i )
  {
    switch( axco_get_device_type(i) )
    {
      case AXCO_DEV_KEYBOARD:
        {
          if( -1 == keyboard_id )
          {
            AXE_INFO( "Keyboard found" );
            keyboard_id = i;
            axco_set_device_active( i, AXE_TRUE );
          }
          else
          {
            AXE_INFO( "Keyboard found, but another keyboard is already in use" );
          }
        }

        break;

      case AXCO_DEV_MOUSE:
        {
          if( -1 == mouse_id )
          {
            AXE_INFO( "Mouse found" );
            mouse_id = i;
            axco_set_device_active( i, AXE_TRUE );
          }
          else
          {
            AXE_INFO( "Mouse found, but another mouse is already in use" );
          }
        }

        break;

      case AXCO_DEV_JOY:
        AXE_INFO( "Joystick found, but there is no support for joysticks yet" );
        break;

      default:
        AXE_ASSERT( false );
        break;
    }
  }

  AXE_ASSERT( keyboard_id >= 0 && mouse_id >= 0 );

  axco_set_update_rate(0.01f);
}

/**
* Update
*/
void axen_control::update( float elapsed_time )
{
  axco_update();

  const axco_alert_fired*   alerts = axco_get_alerts_fired();
  for( register unsigned int i = 0; i < axco_get_num_alerts_fired(); ++i )
  {
    const axco_alert_fired*   alert = axco_get_alerts_fired( i );
    //engine->on_input( alert->alert_id );
  }
}

/**
* Done
*/
void axen_control::done()
{
  axco_done();
}

/**
* Adds an alert to the specified key
*/
void axen_control::add_alert( AXE_ID event_id, unsigned int key )
{
  axco_begin_alert( event_id );
  axco_add_event( keyboard_id, key, AXCO_KEY_PRESS );
  axco_end_alert();
}

/**
* Adds an alert to the specified key
*/
bool axen_control::is_key_down( unsigned int key ) const
{
  if (axco_is_key_pressed(keyboard_id, key) == AXE_TRUE)
  {
    return(true);
  }

  return(false);
}

/**
* Adds an alert to the specified key
*/
void  axen_control::get_mouse_steering( int *x, int *y ) const
{
  axco_get_mouse_motion( mouse_id, x, y );
}


/* $Id: axen_control.cpp,v 1.1 2004/09/20 21:28:14 doneval Exp $ */
