/**
* @file
* Axe 'math' test code
* @see axe_math.h
*/
#include "axmt_test.h"
#include "axmt_timer.h"

#define AXMT_NO_AUTOLINK
#include "../src/axe_math.h"

/// Version of this test code
#define AXE_MATH_TEST_VERSION 1

// Use proper library --------
#ifdef _DEBUG
  #pragma comment( lib, "../../../output_debug/lib/axe_math.lib" )
#else
  #pragma comment( lib, "../../../output_release/lib/axe_math.lib" )
#endif

/**
* Checks if this code and the lib have the same version
*/
int check_versions() {
  printf( "\nGetting lib version ... " );

  if( AXE_MATH_VERSION != AXE_MATH_TEST_VERSION ) {
    printf(
      "This test program and the library versions differ! Lib:%d Test:%d\n",
      AXE_MATH_VERSION,
      AXE_MATH_TEST_VERSION );
    getchar();
    return( 0 );
  }

  printf( "Library Version: %d - This testing program: %d\n\n", AXE_MATH_VERSION, AXE_MATH_TEST_VERSION );

  return( 1 );
}

#define axe_TEST_NUM  999999

/**
* Simple code to test all functionality of the library
*/
int main() {
  int         i;
  axmt_timer  t;

  printf( "Axe 'math' library test STARTED\n" );

  // Check versions ------------------------------------
  if( check_versions() == 0 ) {
    return( 0 );
  }

  //*************************************************************************************
  // NOT OPTIMIZED VECTOR2 -----------------------------
  printf( "Managing %d axe_vector2 ----------------------\n", axe_TEST_NUM );

  axe_vector2 tmp2;

  tmp2.zero();
  printf( "zeroing: %f, %f\n", tmp2.x, tmp2.y );

  tmp2.create( 1.0f, 2.0f );
  printf( "set 1,2: %f, %f\n", tmp2.x, tmp2.y );

  tmp2 = tmp2 + tmp2;
  printf( "a=a+a: %f, %f\n", tmp2.x, tmp2.y );

  tmp2 = tmp2 / 2;
  printf( "a=a/2: %f, %f\n", tmp2.x, tmp2.y );

  tmp2 = tmp2 - tmp2;
  printf( "a=a-a: %f, %f\n", tmp2.x, tmp2.y );

  t.start();

  axe_vector2*  p = new axe_vector2[axe_TEST_NUM];
  t.stop();
  printf( "new v2:\t%f secs\n", t.elapsedf() );

  // -----------------------
  i = 0;
  t.start();
  for( ; i < axe_TEST_NUM; ++i ) {
    p[i].zero();
  }

  t.stop();
  printf( "v2.zer:\t%f secs\n", t.elapsedf() );

  // -----------------------
  i = 0;
  t.start();
  tmp2.create( 2.0f, 2.0f );
  for( ; i < axe_TEST_NUM; ++i ) {
    p[i] = tmp2;
  }

  t.stop();
  printf( "v2 = :\t%f secs\n", t.elapsedf() );

  // -----------------------
  i = 0;
  t.start();
  for( ; i < axe_TEST_NUM; ++i ) {
    tmp2 = p[i] + p[i];
  }

  t.stop();
  printf( "v2+v2:\t%f secs\n", t.elapsedf() );

  // -----------------------
  i = 0;
  t.start();
  for( ; i < axe_TEST_NUM; ++i ) {
    tmp2 = p[i] - p[i];
  }

  t.stop();
  printf( "v2-v2:\t%f secs\n", t.elapsedf() );

  // -----------------------
  i = 0;
  t.start();
  for( ; i < axe_TEST_NUM; ++i ) {
    p[i] * p[i];
  }

  t.stop();
  printf( "v2*v2:\t%f secs\n", t.elapsedf() );

  // -----------------------
  i = 0;
  t.start();
  for( ; i < axe_TEST_NUM; ++i ) {
    tmp2 = p[i] / 0.324f;
  }

  t.stop();
  printf( "v2/fl:\t%f secs\n", t.elapsedf() );

  // -----------------------
  i = 0;
  t.start();
  for( ; i < axe_TEST_NUM; ++i ) {
    p[i] == p[i];
  }

  t.stop();
  printf( "v2==v2:\t%f secs\n", t.elapsedf() );

  // -----------------------
  i = 0;
  t.start();
  for( ; i < axe_TEST_NUM; ++i ) {
    p[i] != p[i];
  }

  t.stop();
  printf( "v2!=v2:\t%f secs\n", t.elapsedf() );

  // --- debugger test
  axe_vector2i  t2i;
  t2i.create( 343455, -123 );

  axe_vector3 t3;
  t3.create( 3.1435f, 1.0f, -23.0001f );

  axe_vector4 t4;
  t4.create( 3.1435f, -1.0f, 1.0004500f, 1.0f );

  axe_euler_angles  te;

  te.create( 1.57f, 3.14152192f, 0.2f );

  axe_matrix_3x3  t33;
  t33.create( t3, t3, t3 );

  axe_matrix_4x3  t43;
  t43.create( t3, t3, t3, t3 );

  axe_matrix_4x4  t44;
  t44.create( t3, t3, t3, t3 );

  axe_quaternion  tq;
  tq.create( 3.1435f, -1.0f, 1.0004500f, 1.0f );

  // -----------------------
  t.start();
  delete[] p;
  t.stop();
  printf( "delete:\t%f secs\n", t.elapsedf() );

  //*************************************************************************************
  // SSE OPTIMIZED VECTOR2 -----------------------------
  /*
	printf("\nManaging %d axe_vector2 SSE -------------------\n", axe_TEST_NUM);
	axe_sse_vector2 tmp2_sse;
	
	tmp2_sse.zero();
	printf("zeroing: %f, %f\n", tmp2_sse.x, tmp2_sse.y);

	tmp2_sse = axe_sse_vector2(1.0f, 2.0f);
	printf("set 1,2: %f, %f\n", tmp2_sse.x, tmp2_sse.y);
	
	axe_sse_vector2 tmp2_sse2(tmp2_sse);
	printf("set 1,2: %f, %f\n", tmp2_sse2.x, tmp2_sse2.y);

	tmp2_sse = tmp2_sse+1.5f;
	printf("a=a+1.5: %f, %f\n", tmp2_sse.x, tmp2_sse.y);

	tmp2_sse = tmp2_sse+tmp2_sse;
	printf("a=a+a: %f, %f\n", tmp2_sse.x, tmp2_sse.y);

	tmp2_sse = tmp2_sse*tmp2_sse;
	printf("a=a*a: %f, %f\n", tmp2_sse.x, tmp2_sse.y);

	tmp2_sse = tmp2_sse/2;
	printf("a=a/2: %f, %f\n", tmp2_sse.x, tmp2_sse.y);

	tmp2_sse = tmp2_sse-tmp2_sse;
	printf("a=a-a: %f, %f\n", tmp2_sse.x, tmp2_sse.y);

	t.start();
	axe_sse_vector2 *p_sse = new axe_sse_vector2[axe_TEST_NUM];
	t.stop();
	printf("Creation in:\t%f secs\n", t.elapsedf());

	// -----------------------
	i=0;
	t.start();
	for(;i<axe_TEST_NUM;++i) {
		p_sse[i].zero();
	}
	t.stop();
	printf("Zeroing in:\t%f secs\n", t.elapsedf());

	// -----------------------
	i=0;
	t.start();
	for(;i<axe_TEST_NUM;++i) {
		p_sse[i] = axe_sse_vector2(2.0f, 2.0f);
	}
	t.stop();
	printf("Operator = in:\t%f secs (with vector2(f,f) constructor)\n", t.elapsedf());

	// -----------------------
	i=0;
	axe_sse_vector2 v2_sse(1.5f, 1.5f);
	t.start();
	for(;i<axe_TEST_NUM;++i) {
		p_sse[i] = axe_sse_vector2(v2_sse);
	}
	t.stop();
	printf("Operator = in:\t%f secs (with vector2(vector2) constructor)\n", t.elapsedf());

	// -----------------------
	i=0;
	t.start();
	for(;i<axe_TEST_NUM;++i) {
		tmp2_sse = p_sse[i] + 0.5;
	}
	t.stop();
	printf("Operator + in:\t%f secs (vector+float)\n", t.elapsedf());

	// -----------------------
	i=0;
	t.start();
	for(;i<axe_TEST_NUM;++i) {
		tmp2_sse = p_sse[i] + p_sse[i];
	}
	t.stop();
	printf("Operator + in:\t%f secs (vector+vector)\n", t.elapsedf());

	// -----------------------
	i=0;
	t.start();
	for(;i<axe_TEST_NUM;++i) {
		tmp2_sse = p_sse[i] - p_sse[i];
	}
	t.stop();
	printf("Operator - in:\t%f secs\n", t.elapsedf());

	// -----------------------
	i=0;
	t.start();
	for(;i<axe_TEST_NUM;++i) {
		tmp2_sse = p_sse[i] * p_sse[i];
	}
	t.stop();
	printf("Operator * in:\t%f secs\n", t.elapsedf());

	// -----------------------
	i=0;
	t.start();
	for(;i<axe_TEST_NUM;++i) {
		tmp2_sse = p_sse[i] / p_sse[i];
	}
	t.stop();
	printf("Operator / in:\t%f secs\n", t.elapsedf());

	// -----------------------
	i=0;
	t.start();
	for(;i<axe_TEST_NUM;++i) {
		tmp2_sse = p_sse[i] / 0.324f;
	}
	t.stop();
	printf("Operator / in:\t%f secs (vector-float)\n", t.elapsedf());

	// -----------------------
	i=0;
	t.start();
	for(;i<axe_TEST_NUM;++i) {
		p_sse[i] /= p_sse[i];
	}
	t.stop();
	printf("Operator /= in:\t%f secs\n", t.elapsedf());

	// -----------------------
	i=0;
	t.start();
	for(;i<axe_TEST_NUM;++i) {
		p_sse[i] == p_sse[i];
	}
	t.stop();
	printf("Operator == in:\t%f secs\n", t.elapsedf());

	// -----------------------
	i=0;
	t.start();
	for(;i<axe_TEST_NUM;++i) {
		p_sse[i] != p_sse[i];
	}
	t.stop();
	printf("Operator != in:\t%f secs\n", t.elapsedf());

	// -----------------------
	t.start();
	delete[] p_sse;
	t.stop();
	printf("Deletion in:\t%f secs\n", t.elapsedf());

	//*************************************************************************************
	// 3dnow OPTIMIZED VECTOR2 -----------------------------
	printf("\nManaging %d axe_vector2 3dow! -------------------\n", axe_TEST_NUM);
	axe_3dnow_vector2 tmp2_3dnow;

	tmp2_3dnow.zero();
	printf("zeroing: %f, %f\n", tmp2_3dnow.x, tmp2_3dnow.y);

	tmp2_3dnow = axe_3dnow_vector2(1.0f, 2.0f);
	printf("set 1,2: %f, %f\n", tmp2_3dnow.x, tmp2_3dnow.y);

	axe_3dnow_vector2 tmp2_3dnow2(tmp2_3dnow);
	printf("set 1,2: %f, %f\n", tmp2_3dnow2.x, tmp2_3dnow2.y);

	tmp2_3dnow = tmp2_3dnow+1.5f;
	printf("a=a+1.5: %f, %f\n", tmp2_3dnow.x, tmp2_3dnow.y);

	tmp2_3dnow = tmp2_3dnow+tmp2_3dnow;
	printf("a=a+a: %f, %f\n", tmp2_3dnow.x, tmp2_3dnow.y);

	tmp2_3dnow = tmp2_3dnow*tmp2_3dnow;
	printf("a=a*a: %f, %f\n", tmp2_3dnow.x, tmp2_3dnow.y);

	tmp2_3dnow = tmp2_3dnow/2;
	printf("a=a/2: %f, %f\n", tmp2_3dnow.x, tmp2_3dnow.y);

	tmp2_3dnow = tmp2_3dnow-tmp2_3dnow;
	printf("a=a-a: %f, %f\n", tmp2_3dnow.x, tmp2_3dnow.y);

	// -----------------------
	t.start();
	axe_3dnow_vector2 *p_3dnow = new axe_3dnow_vector2[axe_TEST_NUM];
	t.stop();
	printf("Creation in:\t%f secs\n", t.elapsedf());

	// -----------------------
	i=0;
	t.start();
	for(;i<axe_TEST_NUM;++i) {
		p_3dnow[i].zero();
	}
	t.stop();
	printf("Zeroing in:\t%f secs\n", t.elapsedf());

	// -----------------------
	i=0;
	t.start();
	for(;i<axe_TEST_NUM;++i) {
		p_3dnow[i] = axe_3dnow_vector2(2.0f, 2.0f);
	}
	t.stop();
	printf("Operator = in:\t%f secs (with vector2(f,f) constructor)\n", t.elapsedf());

	// -----------------------
	i=0;
	t.start();
	for(;i<axe_TEST_NUM;++i) {
		tmp2_3dnow = p_3dnow[i] + 0.5;
	}
	t.stop();
	printf("Operator + in:\t%f secs (vector+float)\n", t.elapsedf());

	// -----------------------
	i=0;
	t.start();
	for(;i<axe_TEST_NUM;++i) {
		tmp2_3dnow = p_3dnow[i] + p_3dnow[i];
	}
	t.stop();
	printf("Operator + in:\t%f secs (vector+vector)\n", t.elapsedf());

	// -----------------------
	t.start();
	delete[] p_3dnow;
	t.stop();
	printf("Deletion in:\t%f secs\n", t.elapsedf());
*/
  // Finish --------------------------------------------
  printf( "\nAxe 'math' library test FINISHED\n" );
  getchar();
  return( 1 );
}

/* $Id: axmt_test.cpp,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
