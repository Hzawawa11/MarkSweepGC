#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "basic.h"

Object* R[RN];

Object* HtopINT;
Object* HbtmINT;
Object* HtopPAIR;
Object* HbtmPAIR;
Object* freelistINT;
Object* freelistPAIR;

Object* gcs[STACKSIZE];
int stackpoint;
Object* local[STACKSIZE];
int local_sp;


#define isPair(o) (_TYPE(o) == T_PTR)
#define isMarked(o) (o->Dummy.mark == TRUE)
#define GCS_EMPTY() (stackpoint == 0)



void init_free(void){
  Object* freetmp;

  freelistPAIR = (Object*)malloc(HEAPSIZE/2);
  freelistINT = (Object*)malloc(HEAPSIZE/2);

  HbtmPAIR = freelistPAIR;
  HbtmINT = freelistINT;

  for(int i = 0; i < ((HEAPSIZE/2)/PAIRSIZE); i++){
    freetmp = (u_int64_t)HbtmPAIR + (PAIRSIZE*i);
    _TYPE(freetmp) = T_PTR;
    _MARK(freetmp) = 'f';
    car(freetmp) = NULL;
    cdr(freetmp) = freelistPAIR;
    freelistPAIR = freetmp;
  }
  HtopPAIR = freelistPAIR;

  for(int i = 0; i < ((HEAPSIZE/2)/DINTSIZE); i++){
    freetmp = (u_int64_t)HbtmINT + (DINTSIZE*i);
    _TYPE(freetmp) = T_INT;
    _MARK(freetmp) = 'f';
    _DLINK(freetmp) = freelistINT;
    freelistINT = freetmp;
  }
  HtopINT = freelistINT;
}

void gc(void){
  init_gcs();
  RootScan();
  mark();
  sweep();
}

void mark(void){
  Object* p;
  while( !GCS_EMPTY() ){ // not isEmpty(worklist)
    p = pop_gcs(); //remove(worklist)
    if(isPair(p)){
      if ( cdr(p) != NULL && !isMarked(cdr(p)))
        push_gcs(cdr(p));
      if ( car(p) != NULL && !isMarked(car(p))) 
        push_gcs(car(p));
    }
  }
}

void sweep(void){
  Object* p = HbtmINT;
  int i = 0;

  for(i = 0; p < HtopINT; i++){
    p = (u_int64_t)HbtmINT+(sizeof(char)*DINTSIZE*i);
    if (_MARK(p) == TRUE){
      _MARK(p) = FALSE;
    }else if (_MARK(p) != 'f'){
      _DLINK(p) = freelistINT;
      freelistINT = p;
      _MARK(freelistINT) = 'f';
    }
  }

  p = HbtmPAIR;
  for(i = 0; p < HtopPAIR; i++){
    p = (u_int64_t)HbtmPAIR+(sizeof(char)*PAIRSIZE*i);
    if (_MARK(p) == TRUE){
      _MARK(p) = FALSE;
    }else if( _MARK(p) != 'f' ){
      cdr(p) = freelistPAIR;
      freelistPAIR = p;
      _MARK(freelistPAIR) = 'f';
    }
  }
}

void RootScan(void){
  int i;
  for(i = 0; i < RN; i++){
    if (R[i] != NULL)
      push_gcs(R[i]); // push and mark
  }
  for(i = 0; i < STACKSIZE; i++){
    if (local[i] != NULL) 
      push_gcs(local[i]); // push and mark
  }
}

void init_gcs(void){
  int i;
  for(i = 0; i < STACKSIZE; i++)
    gcs[i] = NULL;
}

int push_gcs(Object* obj){
  if (stackpoint < STACKSIZE){
    _MARK(obj) = TRUE;
    gcs[stackpoint] = obj;
    stackpoint++;
    return TRUE;
  } else { // Error process
    puts("Error: gcs stack overflow");
    exit(1);
  }
}

Object* pop_gcs(){
  if (stackpoint > 0) {
    stackpoint--;
    return gcs[stackpoint];
  } else {
    return FALSE;
  }
}

void init_local(void){
  int i;
  for(i = 0; i < STACKSIZE; i++)
    local[i] = NULL;
}

int push_local(Object* obj){
  if(obj == NULL)
    return FALSE;
  if (local_sp < STACKSIZE){
    _MARK(obj) = TRUE;
    local[local_sp] = obj;
    local_sp++;
    return TRUE;
  } else { // Error 
    puts("Error: local stack overflow");
    exit(1);
  }
}

Object* pop_local(void){
  if (local_sp > 0) {
    local_sp--;
    _MARK(local[local_sp]) = FALSE;
    return local[local_sp];
  } else {
    return FALSE;
  }
}
