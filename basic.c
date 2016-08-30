#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "basic.h"

Object* freelistINT;
Object* freelistPAIR;

#define EMPTY_LIST(list) (list == NULL)
#define CHECK(o) \
  if(_TYPE(o) != T_INT && _TYPE(o) != T_PTR){\
    puts("Error: 1");exit(0);\
  }

Object* cons(Object* car, Object* cdr){
  
  // CHECK(car); CHECK(cdr);
  if (EMPTY_LIST(freelistPAIR)){
    gc();
    if(EMPTY_LIST(freelistPAIR)){
      exit(0);
    }
  }
  Object* obj = freelistPAIR;
  freelistPAIR = cdr(obj);
  car(obj) = car;
  cdr(obj) = cdr;
  _TYPE(obj) = T_PTR;
  _MARK(obj) = FALSE;
  return obj;
}

Object* atom(int i){
  if (EMPTY_LIST(freelistINT)){
    gc();
    if(EMPTY_LIST(freelistINT)){
      exit(0);
    }
  }  
  Object* obj = freelistINT;
  freelistINT = _DLINK(obj);
  _DINT(obj) = i;
  _TYPE(obj) = T_INT;
  _MARK(obj) = FALSE;
  return obj;
}
