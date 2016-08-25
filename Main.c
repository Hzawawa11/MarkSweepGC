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

/* prototype function */

int main(void){
  init_free();
  state_list();
  /*Int Data*/
  
  Object* int_50 = atom(50);
  Object* int_20 = atom(20);
  init_local();
  push_local(int_20);
  push_local(int_50);
  /*
  int i = 1;
  for( ; i < 20; i++)
    int_50 = atom(20);
*/
  
  /*Pair*/
  R[0] = cons(int_20, int_50);
  R[1] = cons(int_20, int_50);
  int i;
  for(i = 1; i <= 8; i++){
    R[0] = cons(R[0], int_20);
  }
  // RootScan();
  // mark();
  R[0] = int_20;
  R[0] = cons(int_50, int_20);  
  // R[0] = cons(50, 20);  
  state_list();
  state_Obj(R[1]);
  pop_local();
  pop_local();
  free(freelistINT);
  free(freelistPAIR);

}