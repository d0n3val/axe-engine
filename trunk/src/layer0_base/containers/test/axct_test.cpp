/**
* @file
* Axe 'containers' test code
* @see axe_containers.h
*/
#include "axct_test.h"

#define AXST_NO_AUTOLINK
#include "axe_defs.h"
#include "axe_containers.h"
#include "axe_string.h"
#include <crtdbg.h>
#include <vector>
#include <list>

#ifdef _DEBUG
#pragma comment( lib, "../../../output_debug/lib/axe_string.lib" )
#else
#pragma comment( lib, "../../../output_release/lib/axe_string.lib" )
#endif

int array_foreach( int& value, const long index );
int array_sort( int& value1, int& value2 );

int array_foreach( int& value, const long index ) {
  printf( "\n foreach value received: %d at pos %d", value, index );
  return( 1 );
}

int array_sort( int& value1, int& value2 ) {
  if( value1 <= value2 ) {
    return( 1 );
  }

  return( 0 );
}

struct test {
  static int n;
  int me;

  test() {
    me = ++n;
    printf("\nTEST constructor called: %i\n", me);
  }

  ~test() {
    printf("\nTEST destructor called: %i\n", me);
    getchar();
  }
};

int test::n = 0;

void print_bitset(axe_bitset<5>& bitset) {

  printf("\nBitset data: ");
  for( register unsigned int i = 0; i < 5; ++i ) {
    printf("%d ", bitset[i]);
  }

}

void dump_axe_many(axe_many const& table) 
{
  // Dump table
  int i = 0;
  for( axe_list_item < axe_any > *p_item = table.start; p_item != NULL; p_item = p_item->next )
  {
    if (AXE_ANY_IS_TYPE(p_item->data, bool))
    {
      printf("%d: (bool) %s", i, (any_cast<bool>(p_item->data) == true) ? "true" : "false" );
    }
    else if (AXE_ANY_IS_TYPE(p_item->data, char))
    {
      printf("%d: (char) %c", i, any_cast<char>(p_item->data) );
    }
    else if (AXE_ANY_IS_TYPE(p_item->data, int))
    {
      printf("%d: (int) %d", i, any_cast<int>(p_item->data) );
    }
    else if (AXE_ANY_IS_TYPE(p_item->data, float))
    {
      printf("%d: (float) %f", i, any_cast<float>(p_item->data) );
    }
    else if (AXE_ANY_IS_TYPE(p_item->data, double))
    {
      printf("%d: (double) %f", i, any_cast<double>(p_item->data) );
    }
    else if (AXE_ANY_IS_TYPE(p_item->data, const char *))
    {
      printf("%d: (char*) %s", i, any_cast<const char *>(p_item->data) );
    }
    else if (AXE_ANY_IS_TYPE(p_item->data, axe_string))
    {
      //axe_string s = any_cast<axe_string>(p_item->data);
      printf("%d: (axe_string) %s", i, "?" );
    }
    else if (AXE_ANY_IS_TYPE(p_item->data, void *))
    {
      printf("%d: (void*) 0x%p", i, any_cast<void *>(p_item->data) );
    }
    else if (AXE_ANY_IS_TYPE(p_item->data, axe_many))
    {
      axe_any *any = &(p_item->data);
      //axe_list<axe_any> * p = any_cast<axe_many *>(any);
      printf("%d: (axe_many) -------->\n", i);
      //dump_axe_many(any_cast<axe_many>(p_item->data));
      //printf("<----------------------");
    }
    else
    {
      printf("%d: (unknown)", i );
    }

    printf("\n");
    ++i;
  }
}

struct test2 {
  axe_dyn_array<test> list;
};

/**
* Simple code to test all functionality of the library
*/
int main() {
  _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF );
  _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG );
  _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );
  _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_DEBUG );


/*
  axe_bitset<5> bitset;


  bitset.zero();
  
  print_bitset(bitset);
 
  int flags = 5;

  bitset.create(flags, 5);

  print_bitset(bitset);
  
  bool b = bitset.check_enabled(4, 5);
  printf("\n ask if flag '4' is active: %s\n", (b) ? "TRUE" : "FALSE");

  b = bitset.check_enabled(2, 5);
  printf("\n ask if flag '2' is active: %s\n", (b) ? "TRUE" : "FALSE");


  int numbers[5];
  numbers[0] = 111;
  numbers[1] = 222;
  numbers[2] = 333;
  numbers[3] = 444;
  numbers[4] = 555;

  unsigned int  size;

  printf( "Axe 'containers' library test STARTED\n" );

  // Start -------------------------------------------
  printf( "\nCreating list1 ...\n" );

  axe_list<int> list1;

  printf( "\nCreating list2 ...\n" );

  axe_list<int> list2;

  printf( "\nCreating list3 ...\n" );

  axe_list<int> list3;

  printf( "\nAdding '111' item to list1 ...\n" );
  list1.add( numbers[0] );

  printf( "\nAdding '222' item to list1 ...\n" );
  list2.add( numbers[1] );

  printf( "\nAsking for list1 size ...\n" );
  size = list1.size;

  printf( "SIZE = %u\n", size );

  printf( "\nAdding '333' item to list2 ...\n" );
  list2.add( numbers[2] );
*/

  //axe_list<test*> test_list;
  //test *t1;
  //t1 = new test();
  /*
  test t2;
  {
    axe_list<test> test_list;


    test_list.add(t2);

    test_list.clear();

    //printf( "\nClearing ..\n" );
  }*/
  
  //

  /*
  printf( "Deleting active item for list2 ..." );
  axct_list_delete();
   

  printf( "Asking for list2 size ..." );
  size = axct_list_get_size();
   
  printf( "SIZE = %u\n", size );

  printf( "Reading active item for list1 ..." );
  tmp = (int*) axct_list_id_get_data( list1_id );
   
  printf( "DATA = %d\n", *tmp );

  printf( "Setting active item for list1 to 555..." );
  axct_list_id_set_data( list1_id, &numbers[4] )  

  printf( "Reading active item for list1 ..." );
  tmp = (int*) axct_list_id_get_data( list1_id );
   
  printf( "DATA = %d\n", *tmp );

  printf( "Destroying list3 ..." );
  axct_list_id_destroy( list3_id );
   */
  /*
  // Loop example -------------------------------------
  printf( "Looping list 1 ...\n" );
  axct_set_active_list( list1_id ); 

  tmp = (int*) axct_list_start();

  while( tmp != NULL ) {
    printf( "DATA = %d ", *tmp );
    tmp = (int*) axct_list_next();
     
  }
*/

  /*$1- static array test ----------------------------------------------------*/
  /*
  printf( "\n\n*** STATIC ARRAY Before sorting: ***\n" );
  axe_stc_array<int, 6> my_s_array;

  for( register int i = 0; i < 6; ++i ) {
    my_s_array[i] = rand();
  }

  printf( "\nBefore sorting:\n" );
  my_s_array.foreach( array_foreach );

  my_s_array.sort( array_sort );

  printf( "\nAfter sorting:\n" );
  my_s_array.foreach( array_foreach );
*/
  /*$1- dynamic array test ---------------------------------------------------*/
  /*
  printf( "\n\n*** DYNAMIC ARRAY Before sorting: ***\n" );
  axe_dyn_array <int > my_d_array( 3 );

  for( register int i = 0; i < 10; ++i ) {
    my_d_array.push( rand() );
  }

  printf( "\nBefore sorting:\n" );
  my_d_array.foreach( array_foreach );

  my_d_array.sort(array_sort);

  printf( "\nAfter sorting:\n" );
  my_d_array.foreach( array_foreach );
  
  axe_dyn_array<test> my_array(3);

  test a1,a2,a3,a4,a5;

  my_array.push(a1);
  my_array.push(a2);
  my_array.push(a3);
  my_array.push(a4);
  my_array.push(a5);

  axe_dyn_array<test> my_array2;
  my_array2 = my_array;
*/

  /*$1- variant "any" test ---------------------------------------------------*/
  printf( "\n\nAssigning values\n" );
  void *p = NULL;
  const char *ps = "hi world";
  test t1;
  axe_string s("hello world");
  axe_many table;
  axe_many nested_table;

  axe_any n = false;

  bool b = false;
  b = AXE_ANY_IS_TYPE(n, bool);
  b = AXE_ANY_IS_TYPE(n, test);

  n = 3.0f;
  b = AXE_ANY_IS_TYPE(n, test);
  b = AXE_ANY_IS_TYPE(n, float);

  n = ps;
  b = AXE_ANY_IS_SAME_TYPE(n, table);
  b = AXE_ANY_IS_SAME_TYPE(n, p);
  b = AXE_ANY_IS_SAME_TYPE(n, ps);

  nested_table.add(1);
  nested_table.add(2);
  nested_table.add(3);

  //table.add(true);
  //table.add(3);
  //table.add(3.0f);
  //table.add(3.0);
  //table.add(2.02);
  //table.add(ps);
  table.add(nested_table);
  //table.add(p);
  //table.add(ps);
  //////table.add(t1);
  //table.add(t2);
//  table.add(t3);

  // Dump table
  dump_axe_many(table);

  // Finish -------------------------------------------
  printf( "\nAxe 'containers' library test FINISHED\n" );
  getchar();
  return( 1 );
}

/* $Id: axct_test.cpp,v 1.3 2004/07/21 22:08:51 doneval Exp $ */
