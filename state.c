#include <stdio.h>
#include "structure.h"
#include "basic.h"

void state_Obj(Object* obj)
{
  if(obj == NULL){
    goto end;
  }
  printf("Object pointer: %p\n", obj);
  
  if (_TYPE(obj) == T_PTR){
    printf("%10s%s%s","> T_PTR:", (_MARK(obj) == TRUE?"*":" "), "(");
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
    printf("%10s%s(%d)\n", "> T_INT: ", (_MARK(obj) == TRUE?"*":" "), _DINT(obj));
  }
  end: ;
}

void state_list(void){
  Object* fPAIR = freelistPAIR;
  int i = 1;
  printf(" --------   top    ------\n");
  
  while(fPAIR != NULL){
    printf("%5d: %p\n",i++, fPAIR);
    fPAIR = cdr(fPAIR);
  }

  printf(" --------  bottom  ------\n");
/*  
  printf(" --------   top    ------\n");
  
  Object* fINT = freelistINT;
  i = 1;
  while(fINT != NULL){
    printf("%5d: %p\n",i++, fINT);
    fINT =  _DLINK(fINT);
  }
  printf(" --------  bottom  ------\n");
*/
}