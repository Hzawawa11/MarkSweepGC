#include <stdio.h>
#include <stdlib.h>
#include "/Users/hiro/Program/C/GC/MarkSweep/include/structure.h"
#include "/Users/hiro/Program/C/GC/MarkSweep/include/list.h"
#include "/Users/hiro/Program/C/GC/MarkSweep/include/mark.h"

#define ListError(n) (n < 1)

Object* ListMake(int n){
  Object* lead = NULL;
  int i = 1;
  if(ListError(n))
    return NULL;
  for(i = 1; i <= n; i++)
    lead = cons(NULL, lead);
  return lead;
}

void ListDispN(int n, Object* list){
  while(n >= 0){
    if(list == NULL)
      break;
    if(n == 0)
      break;
    list = cdr(list);
    n--;
  }
}

void disp(Object* list){
  /* car phase */
  if(car(list) == NULL)
    printf("'()");
  else if(_TYPE(car(list)) == T_INT)
    printf("%d", _DINT(car(list)) );
  else if(_TYPE(car(list)) == T_PTR)
    ListDisp(list);

  /*cdr phase*/
  if(cdr(list) == NULL)
    printf(" . '()");
  else if(_TYPE(cdr(list)) == T_INT)
    printf(" . %d", _DINT(list) );
  else if(_TYPE(cdr(list)) == T_PTR){
    printf(" ");
    disp(cdr(list));    
  }
}

void ListDisp(Object* list){
  if(car(list) == NULL && cdr(list) == NULL ){
    puts("'()");
    goto end;
  }
  printf("(");
  disp(list);
  printf(")\n");
  end: ; 
}

Object* ListDelete(int n, Object* obj){
  if(ListError(n)){
    if(n == 0) 
      return cdr(obj);
    printf("Error 4\n");
    exit(1);
  }
  Object* premitive = obj;
  Object* pre;
  int i = 1;
  while(obj != NULL){
    if(i == n){
     cdr(pre) = cdr(obj);
     break;
    }
    pre = obj;
    obj = cdr(obj);
    i++;
  }
  return premitive;
}

void ListUpdateN(Object* list, int e){
  while(cdr(list) != NULL){
    car(list) = atom(e);
    list = cdr(list);
  }
}

Object* ListInsert(int n, Object* list){
  
  if(ListError(n)){
    if(n == 0)
      return cons(NULL, list);
    return NULL;
  }
  Object* premitive = list;
  while(list != NULL){
    if(n == 1){
      if(cdr(list) == NULL)
        cdr(list) = cons(NULL, NULL);
      else{
        cdr(list) = cons(NULL, cdr(list));
      }
      break;
    }else{
      list = cdr(list);
      n--;
    }
  }
  return premitive;
}