#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "logic.h"

/*
 * CUnit Test Suite
 */




int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testInit() {
    int N = 1;
    body* star = malloc(sizeof(body) * N);
    init(N, star);
    CU_ASSERT(star->mass != 0);
    free(star);
}



void starSetValue(body* star1, int N) {

  star1->px = N;
  star1->py = N;
  star1->vx = N;
  star1->vy = N;
  star1->fx = N;
  star1->fy = N;
  star1->mass = N;

}


void testUpdate() {

  body* star1 = malloc(sizeof(body));
  starSetValue(star1, 10);
  update(star1, 10);
  CU_ASSERT(star1->px == 160);//Same formula for y
  CU_ASSERT(star1->vx == 20);  //Same formula for y
  free(star1);

}

void testresetForce() {
   body* star1 = malloc(sizeof(body));
   starSetValue(star1, 10);
   resetForce(star1);
   CU_ASSERT(star1->fx == 0);
   CU_ASSERT(star1->fy == 0);
   free(star1);

}

void testaddForce() {
   body* star1 = malloc(sizeof(body));
   body* star2 = malloc(sizeof(body));
   starSetValue(star1, 2);
   starSetValue(star2, 3);
   CU_ASSERT(star1->fx == 2);
   addForce(star1, star2);
   CU_ASSERT(star1->fx == 5);
   free(star1);
   free(star2);
}

void testupdateForces() {
  body* star = malloc(sizeof(body) * 2);
    star[0].px = 2;
    star[0].py = 2;
    star[0].vx = 2;
    star[0].vy = 2;
    star[0].mass = 2;

    star[1].px = 3;
    star[1].py = 3;
    star[1].vx = 3;
    star[1].vy = 3;
    star[1].mass = 3;
    updateForces(2, star);
    printf("%lf",star[1].fx);
    CU_ASSERT(star[1].fx == -3);
    free(star);
}

int main() {
    
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("newcunittest1", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if (NULL == CU_add_test(pSuite, "testInit", testInit) || 
	NULL == CU_add_test(pSuite, "testUpdate", testUpdate) ||
	NULL == CU_add_test(pSuite, "testResetForce", testresetForce) ||
	NULL == CU_add_test(pSuite, "testAddforce", testaddForce) ||
	NULL == CU_add_test(pSuite, "testupdateForces", testupdateForces)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

