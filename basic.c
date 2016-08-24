#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "basic.h"

Object* freelist;

#define EMPTY_LIST() (freelist == NULL)

Object* allocate(void){
  printf("allocate: %p\n", freelist);
  Object* cell = freelist;
  freelist = cdr(cell);
  return cell;
}

Object* cons(Object* car, Object* cdr){
  if (EMPTY_LIST()){
    puts("\ngc start!");
    gc();
    if(EMPTY_LIST()){
      puts("Error!");
      return NULL;
    }
  }
  Object* obj = allocate();
  car(obj) = car;
  cdr(obj) = cdr;
  _PAIR(obj, tt) = T_PTR;
  _PAIR(obj, mark) = 0;
  return obj;
}

Object* atom(int i){
  Object* obj = allocate();  
  _DINT(obj) = i;
  _PAIR(obj, tt) = T_INT;
  _PAIR(obj, mark) = 0;
  return obj;
}
