#include <stdio.h>
#include "/Users/hiro/Program/C/GC/MarkSweep/include/structure.h"
#include "/Users/hiro/Program/C/GC/MarkSweep/include/mark.h"

Object* gcs[STACKSIZE];
int sp;
Object* local[STACKSIZE];
int local_sp;


/* Stack */
void init_gcs(void){
  if(sp != 0){ /* Error */
    printf("Error: Not init_local\n");
    exit(1);
  }
  sp = 0;
}

int push_gcs(Object* obj){
  if(obj == NULL){
    puts("Error: Push NULL object to stack.");
    exit(1);
  }
  if (sp < STACKSIZE){
    _MARK(obj) = TRUE;
    gcs[sp] = obj;
    sp++;
    return TRUE;
  } else { // Error process
    puts("Error: Stack overflow.");
    exit(1);
  }
}

Object* pop_gcs(){
  if (sp > 0) {
    return gcs[--sp];
  } else {
    puts("Error: Empty stack.");
    exit(1);
  }
}

void init_local(void){
  if(local_sp != 0){ /* Error */
    puts("Error: Not init_local");
    exit(1);
  }
  local_sp = 0;
}

int push_local(Object* obj){
  if(obj == NULL){
    puts("Error: Push NULL object to local stack.");
    exit(1);
  }
  if (local_sp < STACKSIZE){
    _MARK(obj) = TRUE;
    local[local_sp] = obj;
    local_sp++;
    return TRUE;
  }else { // Error 
    puts("Error: Local stack overflow.");
    exit(1);
  }
}

Object* pop_local(void){
  if (local_sp > 0) {
    _MARK(local[--local_sp]) = FALSE;
    return local[local_sp];
  } else {
    puts("Error: Empty local stack.");
    exit(1);
  }
}
