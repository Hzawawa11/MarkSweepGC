#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "basic.h"

Object* freelist;
Object* Heap;
Object* Htop;
Object* Hbtm;
Object* gcs[STACKSIZE];
int stackpoint;

#define isCons(o) (_TYPE(o) == T_PTR)
#define isMarked(o) (o->Dummy.mark == 1)
#define GCS_EMPTY() (stackpoint == 0)

void gc(void){
  init_gcs();
  RootScan();
  mark(); /*error*/
  sweep();
}

void mark(void){
  Object* p;
  while( !GCS_EMPTY() ){ // not isEmpty(worklist)
    p = pop_gcs(); //remove(worklist)
    if( isCons(p) ){
      if ( !isMarked(car(p))) push_gcs(car(p));
      if ( !isMarked(cdr(p))) push_gcs(cdr(p)); 
    }
  }
}

void sweep(void){
  Object* p;
  int i;
  for(i = 0; i < FREESIZE; i++){
    p = (Hbtm+i);
    // state_Obj(p);
    if (p->Dummy.mark == TRUE){
      p->Dummy.mark = FALSE;
    }else{
      cdr(p) = freelist;
      freelist = p;
      printf("free: %p\n", freelist);
    }
  }
}

void RootScan(void){
  int i;
  for(i = 0; i < RN; i++)
    if (R[i] != NULL){
      push_gcs(R[i]); // push and mark
    }
}

void init_free(void){
  /* initialzie variable */
  /* not increment GC
  Object* car =  (Object*)malloc(sizeof(Object));
  _DINT(car) = (int)"freelist";
  _PAIR(car, tt) = T_INT;
  _PAIR(car, mark) = 0;
  */

  freelist = NULL; 
  Heap = (Object*)malloc(HEAPSIZE*sizeof(Object));
  /* create freelist */
  int i;
  for(i = 0; i < FREESIZE; i++){
    Object* cell = (Heap+i);
    _TYPE(cell) = T_PTR;
    car(cell) = NULL;
    cdr(cell) = freelist;
    freelist = cell;
    if(i == FREESIZE) Htop = freelist;
    if(i == 0) Hbtm = freelist;
  }
}

void init_gcs(void){
  int i;
  for(i = 0; i < STACKSIZE; i++)
    gcs[i] = NULL;
}

int push_gcs(Object* obj){
  if (stackpoint < STACKSIZE){
    obj->Dummy.mark = TRUE;
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