#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "basic.h"

Object* HtopINT;
Object* HbtmINT;
Object* HtopPAIR;
Object* HbtmPAIR;
Object* HPAIR[FREESIZE];
Object* HINT[FREESIZE];

Object* freelistINT;
Object* freelistPAIR;

Object* Heap;
Object* gcs[STACKSIZE];
int stackpoint;
Object* local[STACKSIZE];
int local_sp;
Object* R[RN];


#define isPair(o) (_TYPE(o) == T_PTR)
#define isMarked(o) (o->Dummy.mark == TRUE)
#define GCS_EMPTY() (stackpoint == 0)

#define DINTSIZE() (sizeof(Object)+sizeof(char)+sizeof(char))
#define PAIRSIZE() (sizeof(Object)+sizeof(Object)+sizeof(char)+sizeof(char))

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
      if ( cdr(p) != NULL && !isMarked(cdr(p))){
          push_gcs(cdr(p));
      }
      if ( car(p) != NULL && !isMarked(car(p))) push_gcs(car(p));
    }
  }
}

void sweep(void){
  Object* p;
  int i;
  for(i = 0; i < FREESIZE; i++){
    // p = (HbtmINT+i);
    p = HINT[i];
    if (_MARK(p) == TRUE){
      _MARK(p) = FALSE;
    }else if (_MARK(p) != 'f'){
      _DLINK(p) = freelistINT;
      freelistINT = p;
      _MARK(freelistINT) = 'f';
      // printf("free: %p\n", freelistINT);
    }
  }

  for(i = 0; i < FREESIZE; i++){
    // p = (HbtmPAIR+i);
    p = HPAIR[i];
    if (_MARK(p) == TRUE){
      // printf("%p\n", p);
      _MARK(p) = FALSE;
    }else if( _MARK(p) != 'f' ){
      printf("free: %p\n", p);  
      cdr(p) = freelistPAIR;
      freelistPAIR = p;
      _MARK(freelistPAIR) = 'f';
      // printf("free: %p\n", freelistPAIR);
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



void init_free(void){
  /* Initialze NULL character */
  freelistINT = NULL;
  freelistPAIR = NULL;

  /* Create freelistINT and freelistPAIR */
  int i;
  for(i = 1; i <= FREESIZE; i++){
    Object* NextINT = (Object*)malloc(DINTSIZE());
    // if(i == 1) HbtmINT = NextINT;
    // if(i == FREESIZE) HtopINT = NextINT;
    HINT[i-1] = NextINT;
    _TYPE(NextINT) = T_INT;
    _MARK(NextINT) = 'f';
    _DLINK(NextINT) = freelistINT;
    freelistINT = NextINT;
  }

  for(i = 1; i <= FREESIZE; i++){
    Object* NextPAIR = (Object*)malloc(PAIRSIZE());
    // if(i == 1) HbtmPAIR = NextPAIR;
    // if(i == FREESIZE) HtopPAIR = NextPAIR;
    HPAIR[i-1] = NextPAIR;
    _TYPE(NextPAIR) = T_PTR;
    _MARK(NextPAIR) = 'f';
    car(NextPAIR) = NULL;
    cdr(NextPAIR) = freelistPAIR;
    freelistPAIR = NextPAIR;
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
  } else { /* Error */
    return FALSE;
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
  } else { /* Error */
    return FALSE;
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
