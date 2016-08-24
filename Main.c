/* 
* Programer: Hanzawa JUNCHI
* Date: 2016, Augast 22
* Abstruct: MarkSweepGC (Stop the world)
*/
#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "basic.h"

Object* R[RN];
Object* freelist;

/* prototype function */
Object* benchmark(Object* pre, Object* i);

int main(void){
	puts("Hello Mark Sweep GC");
  init_free();
  state_list();
  /*Int Data*/
  Object* int_50 = atom(50);
  Object* int_20 = atom(20);

  /*Pair*/
  R[0] = benchmark(cons(int_20, int_50), int_20);
  R[0] = NULL;
  R[0] = benchmark(cons(int_20, int_50), int_20);

}

Object* benchmark(Object* pre, Object* i){
  Object* obj = cons(pre, i); 
  if(freelist == NULL){
    return obj;
  }else{
    benchmark(obj, i);
  }
}