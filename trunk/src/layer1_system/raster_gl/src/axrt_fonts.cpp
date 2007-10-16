/**
* @file
* Misc world matrix functions
*/
#include "axrt_stdafx.h"

/**
* Inits a simple font with WGL extension for debugging
*/
AXRT_API int axrt_init_dbg_font( HDC context, const char* font_name, int font_size )
{
  AXE_CHECK_DBG_ERROR( (state.init == true), 10 );

  BOOL  result;

  /*$1- Create the display list ----------------------------------------------*/
  state.font_id = glGenLists( 96 );

  /*$1- Create the font ------------------------------------------------------*/
  HFONT hfont;
  hfont = CreateFont(
      font_size,                    // Height Of Font
      0,                            // Width Of Font
      0,                            // Angle Of Escapement
      0,                            // Orientation Angle
      0,                            // Font Weight
      FALSE,                        // Italic
      FALSE,                        // Underline
      FALSE,                        // Strikeout
      ANSI_CHARSET,                 // Character Set Identifier
      OUT_DEFAULT_PRECIS,           // Output Precision
      CLIP_DEFAULT_PRECIS,          // Clipping Precision
      PROOF_QUALITY,                // Output Quality
      FF_DONTCARE | DEFAULT_PITCH,  // Family And Pitch
      font_name );                  // Font Name

  /*$1- Selects The Font We Want ---------------------------------------------*/
  SelectObject( context, hfont );

  /*$1- Builds 96 Characters Starting At Character 32 ------------------------*/
  result = wglUseFontBitmaps( context, 32, 96, state.font_id );
  AXE_CHECK_DBG_ERROR( (result == FALSE), 11 );

  /*$1- Erase the font -------------------------------------------------------*/
  DeleteObject( hfont );

  /*$1- All ok ---------------------------------------------------------------*/
  return( AXE_TRUE );
}

/* $Id: axrt_raster.cpp,v 1.1 2004/09/24 17:58:39 doneval Exp $ */
