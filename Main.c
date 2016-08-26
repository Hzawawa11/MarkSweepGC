/* 
* Programer: Hanzawa JUNCHI
* Date: 2016, Augast 22 --
* Abstruct: MarkSweepGC (Stop the world)
*/
#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "basic.h"
#include "list.h"

Object* R[RN];

int main(void){
  init_free();
  state_list();
  /*Int Data*/
  printf("freelist : %d\n", FREESIZE);
  // Object* int_50 = atom(50);
  // Object* int_20 = atom(20);
  init_local();
  // push_local(int_20);
  // push_local(int_50);
  
  R[0] = ListMake(3);
  ListDisp(R[0]);
  R[1] = ListMake(5);
  ListDisp(R[1]);
 
  R[1] = ListDelete(2, R[1]);
  ListDisp(R[1]);
  R[0] = ListMake(3);
 
  ListDisp(R[0]);
  ListDisp(R[1]);

  // R[1] = cons(NULL, NULL);
  // R[0] = ListInsert(1, R[0], R[1]);
  // ListDisp(R[0]);

  // pop_local();
  // pop_local();
  free(freelistINT);
  free(freelistPAIR);
}