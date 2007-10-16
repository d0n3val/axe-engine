
readme:
This file contains AutoText and Code templates that follows
the AXE coding style

readme:
AutoText and Code Template entries used by Visual Assist. 

You can obtain information on the purpose and format of this
file by clicking "Help..." on the Auto Completion tab of the
options dialog. The button will open "readtmpl.txt" in the
Misc subdirectory of the Visual Assist installation directory.
If you are currently in VC++, you can also right-click on the 
string "readtmpl.txt" to display a menu with an Open Document 
item that can open the file for you.

caretPosChar:
§


readme:
AutoText follows. None of the entry names contain a space.


ric:
Ricard Pillosu <doneval\@users.sf.net>

car:
Carlos Fuentes <ilgenio\@users.sf.net>

#d:
#define 
#de:
#define 
#u:
#undef 
#un:
#undef 
#p:
#pragma 
#pr:
#pragma 
#in:
#include "§"
#ins:
#include <§>
#if:
#ifdef §
#endif
#ifn:
#ifndef §
#endif
#el:
#else
#eli:
#elif 
#en:
#endif

a:
assert(§);
A:
ASSERT(§);
r:
return( § );
deb:
#ifdef _DEBUG
	§
#endif
T:
AXE_TRUE
t:
true
F:
AXE_FALSE
f:
false
id:
AXE_ID
N:
NULL
struct:
struct § {
};
ifel:
if ( § ) {
} else {
}
if:
if ( § ) {
}
while:
while ( § ) {
}
do:
do {
	
} while( § );
sw:
switch( § ) 
{
	case :
	{
		
	}
	break;
		
	default:
	{
		
	}
}
for:
for( register unsigned int i = 0; i < §; ++i ) {
	
}

tod:
/** @todo: § */
/:
/// §
/*:
/*$1- § */
/**:
/**
* §
*/
/***:
/**
* @file
* §
*/

readme:
Code Templates follow. All entry names contain a space.


AXE C++ .cpp Header File:
/**
* @file
* %1
* @author    Ricard Pillosu <doneval\@users.sf.net>
* @date      %DAY_02% %MONTHNAME% %YEAR%
*/

#include "ax%2_stdafx.h"

%0

/* $Id: VAssist.tpl,v 1.2 2004/09/12 23:14:38 ilgenio Exp $ */

AXE C++ .cpp Body File:
#include "%1.h"

/**
* Constructor
*/
%1::%1() {
}

/**
* Destructor
*/
%1::~%1() {
}

/**
* Method
*/
int %1::method() {
	
	return ( );
}

AXE C++ .H File header:
/**
* @file
* %1
* @author    Ricard Pillosu <doneval\@users.sf.net>
* @date      %DAY_02% %MONTHNAME% %YEAR%
*/
#ifndef __%3_H__
  #define __%3_H__

  #include "ax%2_stdafx.h"

%0

#endif // __%3_H__

/* $Id: VAssist.tpl,v 1.2 2004/09/12 23:14:38 ilgenio Exp $ */

AXE function definition:
/**
* %0
*/
const AXE_ID %1() {
	state.last_error = 1;
	return(AXE_FALSE);
}

AXE Class definition:
/**
* %0
*/
class %1
{
  public:
    
  public:
    %1();
    ~%1();
};

AXE method definition:
/**
* %0
*/
%1 %2::%3() const {

  return( %1 );
}

AXE Switch 4:
switch( %0 )
{
	case %1:
		{
		
		}
		break;
	case %2:
		{
		
		}
		break;
	case %3:
		{
		
		}
		break;
	case %4:
		{
		
		}
		break;
	default:
		{
		
		}
}
AXE Master .H File header:
/**
* @file
* %0
* @author    %1
* @version   %2
* @date      %DAY_02% %MONTHNAME% %YEAR%
*/


/* $Id: VAssist.tpl,v 1.2 2004/09/12 23:14:38 ilgenio Exp $ */

AXE Singleton .H:
/**
* %2 singleton
*/
class %1
{

  /*$1- Singleton stuff ------------------------------------------------------*/
  public:
    static %1 * create();
    ~ %1();
  private:
    static bool active;
    static %1 * instance;
    %1();
  public:

  /*$1- Methods --------------------------------------------------------------*/
  public:

  /*$1- Properties -----------------------------------------------------------*/
  private:
};

AXE Singleton .CPP:
#include "%1.h"

bool %1::          active = false;
%1  *%1::  instance = NULL;

/*$1- Constructor & Destructor -----------------------------------------------*/

/**
* Constructor
*/
%1::%1()
{
}

/**
* Destructor
*/
%1::~%1()
{
  active = false;
}

/*$1- Singleton stuff --------------------------------------------------------*/

/**
* Singleton creator
*/
%1 *%1::create()
{
  if( active == false )
  {
    instance = new %1;
    active = true;
  }

  return( instance );
}

