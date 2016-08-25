#ifndef STRUCTURE_H
#define STRUCTURE_H

#define T_INT 1 
#define T_PTR 2  

#define _TYPE(o) o->Dummy.tt
#define _MARK(o) o->Dummy.mark
#define _DINT(o) o->Dint.data.i
#define _DLINK(o) o->Dint.data.link
 
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
      union {
        struct mark_O* link;
        int i;
      }data;
    }Dint;
  };
} Object;

#define RN 20
#define STACKSIZE 20
#define FREESIZE 10
#define ADDSIZE 10
#define HEAPSIZE 10

extern Object* gcs[STACKSIZE];
extern int stackpoint;
extern Object* local[STACKSIZE];
extern int local_sp;

extern Object* R[RN];
extern Object* Heap;
extern Object* HtopINT;
extern Object* HbtmINT;
extern Object* HtopPAIR;
extern Object* HbtmPAIR;
extern Object* HPAIR[FREESIZE];
extern Object* HINT[FREESIZE];
extern Object* freelistINT;
extern Object* freelistPAIR;

#endif
