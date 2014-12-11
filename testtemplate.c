/*#include <string.h>*/
#include "CUnit/Basic.h"

#include "alloc_data.h"
#include "collector.h"
#include "delete_std.h"
#include "gc.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

heap_t* heap_kb;
heap_t* heap_mb;
heap_t* heap_lessThan_kb;

/* suite initializing functions */
int init_suite_1(void){
  return 0;
}
int init_suite_2(void){
  heap_kb = initHeap(1000);
  heap_mb = initHeap(1000000);
  heap_lessThan_kb = initHeap(999);
  return 0;
}

/* suite cleaning functions */
int clean_suite_1(void){
  return 0;
}
int clean_suite_2(void){
  free(heap_kb);
  free(heap_mb);
  free(heap_lessThan_kb);
  return 0;
}


/* gc.c testing */
void test_H_INIT(void){
  
}

void test_H_DELETE(void){
  
}

/* gc_heap.c testing */
void TEST_initHeap(void){
  CU_ASSERT_PTR_NOT_NULL(heap_kb);
  CU_ASSERT_PTR_NOT_NULL(heap_mb);
  CU_ASSERT_PTR_NULL(heap_lessThan_kb);
}

void TEST_availSpace(void){
  CU_ASSERT(availSpace(heap_kb) == (1000/2) - (sizeof(void*)*3));
  CU_ASSERT(availSpace(heap_mb) == (1000000/2) - (sizeof(void*)*3));
}

void TEST_getHeapStart(void){
  CU_ASSERT_PTR_EQUAL(getHeapStart(heap_kb), heap_kb);
  CU_ASSERT_PTR_EQUAL(getHeapStart(heap_mb), heap_mb);
}

void TEST_getHeapEnd(void){
  CU_ASSERT_PTR_EQUAL(getHeapEnd(heap_kb), getHeapStart(heap_kb) + (1000/2));
  CU_ASSERT_PTR_EQUAL(getHeapEnd(heap_mb), getHeapStart(heap_mb) + (1000000/2));
}

void TEST_getFreeSpaceStart(void){
  CU_ASSERT_PTR_EQUAL(getFreeSpaceStart(heap_kb), getHeapStart(heap_kb) + (sizeof(void*)*3));
  CU_ASSERT_PTR_EQUAL(getFreeSpaceStart(heap_mb), getHeapStart(heap_mb) + (sizeof(void*)*3));
}

/* starting point of the test program */
int main()
{
  CU_pSuite pSuite1 = NULL;
  CU_pSuite pSuite2 = NULL;
  
  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suites to the registry */
  pSuite1 = CU_add_suite("gc.h suite", init_suite_1, clean_suite_1);
  if (NULL == pSuite1){
      CU_cleanup_registry();
      return CU_get_error();
  }
  pSuite2 = CU_add_suite("gc_heap.h suite", init_suite_2, clean_suite_2);
  if (NULL == pSuite2){
      CU_cleanup_registry();
      return CU_get_error();
  }
  
  /* add the tests to the suites */
  if((NULL == CU_add_test(pSuite1, "test of h_init", test_H_INIT)) ||
     (NULL == CU_add_test(pSuite1, "test of h_delete", test_H_DELETE))){
     CU_cleanup_registry();
     return CU_get_error();
    }

  if((NULL == CU_add_test(pSuite2, "TEST_initHeap", TEST_initHeap)) ||
     (NULL == CU_add_test(pSuite2, "TEST_availSpace", TEST_availSpace)) ||
     (NULL == CU_add_test(pSuite2, "TEST_getHeapStart", TEST_getHeapStart)) ||
     (NULL == CU_add_test(pSuite2, "TEST_getHeapEnd", TEST_getHeapEnd)) ||
     (NULL == CU_add_test(pSuite2, "TEST_getFreeSpaceStart", TEST_getFreeSpaceStart))){
     CU_cleanup_registry();
     return CU_get_error();
    }


  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}

