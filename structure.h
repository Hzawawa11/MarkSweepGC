#ifndef STRUCTURE_H
#define STRUCTURE_H

#define T_INT 1 
#define T_PTR 2  

#define _TYPE(o) o->Dummy.tt
#define _DINT(o) o->Dint.i
#define _PAIR(o,d) o->Pair.d
 
/* Data Structure */
typedef struct mark_O{
  union {
    struct{
      char tt;
      char mark;
    }Dummy;
    struct{
      char tt;
      char mark;
      struct mark_O* car;
      struct mark_O* cdr;
    }Pair;
    struct{
      char tt;
      char mark;
      // union {
      int i;
        // struct mark_O* link;
      // }data;
    }Dint;
  };
} Object;

#define RN 20
#define STACKSIZE 20
#define FREESIZE 10
#define ADDSIZE 10
#define HEAPSIZE 100

extern Object* gcs[STACKSIZE];
extern int stackpoint;
extern Object* R[RN];
extern Object* Heap;
extern Object* Htop;
extern Object* Hbtm;
extern Object* freelist;

#endif
