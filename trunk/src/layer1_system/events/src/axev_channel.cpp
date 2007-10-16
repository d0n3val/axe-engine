/**
* @file
* Channel management
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      25 Jul 2004
*/
#include "axev_stdafx.h"

/**
* Create a new event channel
*/
AXEV_API AXE_ID axev_create_channel() {
  channel   my_channel;
  channel*  p_channel = &my_channel;
  int       found = -1;

  for( register int i = 0; i < state.channels.last_item; ++i ) {
    if( true == state.channels[i].destroyed ) {
      p_channel = &state.channels[i];
      found = i;
      break;
    }
  }

  p_channel->active = true;
  p_channel->destroyed = false;

  if( found >= 0 ) {
    return( found );
  }

  state.channels.push( *p_channel );
  return( state.channels.last_item-1 );
}

/**
* Create a new event channel
*/
AXEV_API int axev_destroy_channel( AXE_ID channel_id ) {
  AXE_ASSERT( state.channels.exist(channel_id) );
  AXE_ASSERT( false == state.channels[channel_id].destroyed );

  state.channels[channel_id].destroyed = true;
  state.channels[channel_id].active = false;
  return( AXE_TRUE );
}

/**
* Create a new event channel
*/
AXEV_API int axev_channel_active( AXE_ID channel_id, int active ) {
  AXE_ASSERT( state.channels.exist(channel_id) );
  AXE_ASSERT( false == state.channels[channel_id].destroyed );

  state.channels[channel_id].active = AXE_TO_BOOL(active);

  return( AXE_TRUE );
}

/* $Id: axev_channel.cpp,v 1.1 2004/07/27 22:42:49 doneval Exp $ */
