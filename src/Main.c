/* 
* Programer: Hanzawa JUNCHI
* Date: 2016, Augast 22 --
* Abstruct: MarkSweepGC (Stop the world)
*/
#include <stdio.h>
#include <stdlib.h>
#include "/Users/hiro/Program/C/GC/MarkSweep/include/structure.h"
#include "/Users/hiro/Program/C/GC/MarkSweep/include/mark.h"
#include "/Users/hiro/Program/C/GC/MarkSweep/include/list.h"

Object* R[RN];

int counter_pair = 0;
int counter_dint = 0;

int main(void){
  init_free();

  benchmark();
  // benchmark2();
  // benchmark3();

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