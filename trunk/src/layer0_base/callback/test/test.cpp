/**
* @file
* Axe 'callback' test code
* @see axe_callback.h
*/
#include "test.h"

#include "../src/axe_callback.h"

/// Version of this test code
#define AXE_CALLBACK_TEST_VERSION 1

int function_callback( int i ) {
  return( 2 );
}

class class_callback
{
  public:
    int method_callback( int i ) {
      return( i + 1 );
    }
};

typedef axcb_callbackcontainer<int, int> tmy_callback;

template<class Object, class return_type, class param_type>
axcb_callbackcontainer<return_type, param_type>* create_callback_method(Object* obj, return_type ( Object:: *method ) (param_type))
{
  axcb_callbackmethod<Object, return_type, param_type>* my_method = new axcb_callbackmethod<Object, return_type, param_type>( obj, method);
  return((axcb_callbackcontainer<return_type, param_type>*)my_method);
}

/**
* Simple code to test all functionality of the library
*/
int main() {
  printf( "Axe 'callback' header test STARTED\n" );

  /*$1- Start ----------------------------------------------------------------*/
  axcb_callbackfunction<int, int> function( function_callback );

  int a = 6;
  a = function( a );

  printf("callback function result: %d\n", a);

  class_callback  obj;
  //axcb_callbackmethod<class_callback, int, int> method( &obj, class_callback::method_callback );
  tmy_callback* method = create_callback_method(&obj, class_callback::method_callback);
  
  void *p = (void*) method;

  axcb_callbackcontainer<int, int>* pCallback = (axcb_callbackcontainer<int, int>*)p;
  a = (*pCallback)(a);
    
  //create_callback_method(&obj, class_callback::method_callback);
  //a = method( a );

  printf("callback method result: %d\n", a);

  /*$1- Finish ---------------------------------------------------------------*/
  printf( "\nAxe 'callback' header test FINISHED\n" );
  getchar();
  return( 1 );
}


/* $Id: test.cpp,v 1.2 2004/08/31 07:38:04 ilgenio Exp $ */
