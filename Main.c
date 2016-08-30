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
#define MARK

Object* R[RN];

int main(void){
  init_free();
  // state_list();

  // benchmark();
  puts("\n\n");
  // benchmark2();
  puts("\n\n");
  benchmark3();

  /*Int Data*/
  // Object* int_50 = atom(50);
  // Object* int_20 = atom(20);
  // R[1] = cons(int_50, int_20);
  // printf("(%d . %d)\n", _DINT(car(R[1])), _DINT(cdr(R[1])));
  // R[1] = cons(int_50, int_20);
  // gc();

  /*
  R[0] = ListMake(3);
  ListDisp(R[0]);

  R[1] = ListMake(5);
  ListDisp(R[1]);
 
  R[1] = ListDelete(2, R[1]);
  ListDisp(R[1]);
  R[0] = ListMake(3);
 
  ListDisp(R[0]);
  ListDisp(R[1]);
  */
}