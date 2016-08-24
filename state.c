#include <stdio.h>
#include "structure.h"
#include "basic.h"

void state_Obj(Object* obj)
{
  printf("Object pointer: %p\n", obj);
  
  if (_TYPE(obj) == T_PTR){
    printf("%10s%s%s","> T_PTR:", (obj->Dummy.mark == 1?"*":" "), "(");
    switch(_TYPE(car(obj))){
    case T_INT:
      printf("%d", _DINT(car(obj)));
      break;
    case T_PTR:
      printf("%p", car(obj));
      break;
    default:
      break;
    }
    printf(".");
    switch(_TYPE(cdr(obj))){
    case T_INT:
      printf("%d",_DINT(cdr(obj)));
      break;
    case T_PTR:
      printf("%p", cdr(obj));
      break;
    default:
      break;
    }
    printf(")\n");
  }else if (_TYPE(obj) == T_INT){
    printf("%10s%s(%d)\n", "> T_INT: ", (obj->Dummy.mark == 1?"*":" "),_DINT(obj));
  }
  
}

void state_list(void){
  printf(" --------   top    ------\n");
  Object* tmp = freelist;
  int i = 1;
  while(tmp != NULL){
    printf("%5d: %p\n",i++, tmp);
    tmp = cdr(tmp);
  }
  printf(" --------  bottom  ------\n");
}