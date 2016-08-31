#include <stdio.h>
#include <stdlib.h>
#include "/Users/hiro/Program/C/GC/MarkSweep/include/structure.h"
#include "/Users/hiro/Program/C/GC/MarkSweep/include/mark.h"

Object* R[RN];

Object* HtopINT;
Object* HbtmINT;
Object* HtopPAIR;
Object* HbtmPAIR;
Object* freelistINT;
Object* freelistPAIR;

int counter_dint;
int counter_pair;

#define isPair(o) (_TYPE(o) == T_PTR)
#define isMarked(o) (o->Dummy.mark == TRUE)
#define GCS_EMPTY() (sp == 0)

void init_free(void){
  Object* pair;
  Object* dint;

  if((freelistPAIR = (Object*)malloc(HEAPSIZE/2)) == NULL)
    Error("Can't allcate malloc()");
  if((freelistINT  = (Object*)malloc(HEAPSIZE/2)) == NULL)
    Error("Can't allcate malloc()");

  pair = HbtmPAIR = freelistPAIR;

  /* NULL initialize*/
  _TYPE(freelistPAIR) = T_PTR;
  _MARK(freelistPAIR) = 'f';
  cdr(freelistPAIR) = NULL;
  car(freelistPAIR) = NULL;
  for(int i = 2; i < MAXPAIR; i++){
    pair = (u_int64_t)pair + PAIRSIZE;
    _TYPE(pair) = T_PTR;
    _MARK(pair) = 'f';
    cdr(pair) = NULL;
    _LINK(pair) = freelistPAIR;
    freelistPAIR = pair;
  }
  HtopPAIR = freelistPAIR;
  
  dint = HbtmINT = freelistINT;
  _TYPE(freelistINT) = T_INT;
  _MARK(freelistINT) = 'f';
  cdr(freelistINT) = NULL;
  car(freelistINT) = NULL;
  for(int i = 2; i < MAXDINT; i++){
    dint = (u_int64_t)dint + DINTSIZE;  
    _TYPE(dint) = T_INT;
    _MARK(dint) = 'f';
    _LINK(dint) = freelistINT;
    freelistINT = dint;
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
  for(int i = 0; p < HtopINT; i++){
    if (_MARK(p) == TRUE){
      _MARK(p) = FALSE;
    }else if (_MARK(p) != 'f'){
      _LINK(p) = freelistINT;
      freelistINT = p;
      _MARK(freelistINT) = 'f';
      counter_dint--;
    }
    p = (u_int64_t)p + DINTSIZE;
  }

  p = HbtmPAIR;
  for(int i = 0; p < HtopPAIR; i++){
    if (_MARK(p) == TRUE){
      _MARK(p) = FALSE;
    }else if(_MARK(p) != 'f'){
      _LINK(p) = freelistPAIR;
      freelistPAIR = p;
      _MARK(freelistPAIR) = 'f';
      counter_pair--;
    }
    p = (u_int64_t)p + PAIRSIZE;
  }
}

void RootScan(void){
  for(int i = 0; i < RN; i++)
    if (R[i] != NULL)
      push_gcs(R[i]); 

  for(int i = 0; i < local_sp; i++)
    push_gcs(pop_local()); 
}