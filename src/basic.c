#include <stdio.h>
#include <stdlib.h>
#include "/Users/hiro/Program/C/GC/MarkSweep/include/structure.h"
#include "/Users/hiro/Program/C/GC/MarkSweep/include/mark.h"

Object* freelistPAIR;
Object* freelistINT;

int counter_pair;
int counter_dint;

#define EMPTY_LIST(list) (list == NULL)

Object* cons(Object* car, Object* cdr){
  if (EMPTY_LIST(freelistPAIR)){
    printf("%lf %% (%d/%.lf) mark GC\n", (double)(counter_pair/MAXPAIR), counter_pair, MAXPAIR);  
    gc();
    if(EMPTY_LIST(freelistPAIR))
      Error("Not Empty freelistPAIR");
  }
  Object* obj = freelistPAIR;
  if(_TYPE(obj) != T_PTR)
    Error(" Allocate Object(PAIR) is diffrent TYPE");
  if(_MARK(obj) != 'f')
    Error(" Allocate Object(PAIR) is not initialization");
  freelistPAIR = _LINK(obj);
  _MARK(obj) = FALSE; 
  car(obj) = car;
  cdr(obj) = cdr;
  counter_pair++;
  return obj;
}

Object* atom(int i){
  if (EMPTY_LIST(freelistINT)){
    printf("%lf %% (%d/%.lf) mark GC\n", (double)counter_dint/MAXDINT, counter_dint, MAXDINT);  
    gc();
    if(EMPTY_LIST(freelistINT))
      Error("Not Empty freelistINT");
  }  
  Object* obj = freelistINT;
  if(_TYPE(obj) != T_INT)
    Error(" Allocate diffrent TYPE Object(INT).");
  if( _MARK(obj) != FALSE)
    Error(" Allocate not initialize Object(INT).");
  freelistINT = _DLINK(obj);
  _DINT(obj) = i;
  counter_dint++;
  return obj;
}
