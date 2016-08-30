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

#define DINTSIZE (sizeof(Object)+sizeof(char)+sizeof(char))
#define PAIRSIZE (sizeof(Object)+sizeof(Object)+sizeof(char)+sizeof(char))

#define LISTSIZE 100000

#define RN 5
#define STACKSIZE 1000000

#define MB 1000000
#define MEM 512
#define HEAPSIZE (sizeof(char)*MEM*MB)

extern Object* gcs[STACKSIZE];
extern int stackpoint;
extern Object* local[STACKSIZE];
extern int local_sp;

extern Object* R[RN];
extern Object* HtopINT;
extern Object* HbtmINT;
extern Object* HtopPAIR;
extern Object* HbtmPAIR;
extern Object* freelistINT;
extern Object* freelistPAIR;

#endif
