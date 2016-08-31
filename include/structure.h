#ifndef STRUCTURE_H
#define STRUCTURE_H

#define TRUE 1
#define FALSE 0

#define T_INT 1 
#define T_PTR 2  

#define _TYPE(o) (o->Dummy.tt)
#define _MARK(o) (o->Dummy.mark)
#define _FOWARDING(o) (o->Dummy.mask)
#define _LINK(o) (o->Dummy.mask)
// #define _MASK(o) (o->Dummy.mask)
#define _DINT(o) o->Dint.data.i
#define _DLINK(o) o->Dint.data.link

#define car(o) (o->Pair.car)
#define cdr(o) (o->Pair.cdr)
#define rplaca(o, data) (car(o) = data)
#define rplacd(o, data) (cdr(o) = data)

#define DINT_MARK(o) (o->mark)
#define DINT_TYPE(o) (o->tt)
#define DINT_INT(o) (o->data.i)
#define DINT_LINK(o) (o->data.link)

#define PAIR_MARK(o) (o->mark)
#define PAIR_TYPE(o) (o->tt)
#define PAIR_CDR(o) (o->cdr)
#define PAIR_CAR(o) (o->car)
#define PAIR_LINK(o) (o->car)

#define GCS_EMPTY() (stackpoint == 0)
#define Error(str) {\
  printf("Error:%s.\n", str);\
  exit(1);}
/* Data Structure */
typedef struct dummy{
  char tt;
  char mark;
  struct object* mask;
}Dummy;

typedef struct pair{
  char tt;
  char mark;
  struct object* car;
  struct object* cdr;
}Pair;

typedef struct dint{
  char tt;
  char mark;
  union {
    struct object* link;
    int i;
  }data;
}Dint;

typedef struct object{
  union {
    struct dummy Dummy;
    struct pair Pair;
    struct dint Dint;
  };
}Object;

#define PAIRSIZE (sizeof(struct pair))
#define DINTSIZE (sizeof(struct dint))

#define RN 5
#define STACKSIZE 10

/* Benchmark */
#define LISTSIZE 1000000
#define MB 1000000
#define MEM 256
#define HEAPSIZE (sizeof(char)*MEM*MB)

/* Stack */
extern Object* gcs[STACKSIZE];
extern int sp;
extern Object* local[STACKSIZE];
extern int local_sp;

/* MarkSweepGC */
extern Object* R[RN];
extern Object* HtopINT;
extern Object* HbtmINT;
extern Object* HtopPAIR;
extern Object* HbtmPAIR;
extern Object* freelistINT;
extern Object* freelistPAIR;

/* Magic NUMBER*/
extern int counter_pair;
extern int counter_dint;
#define MAXPAIR (double)((HEAPSIZE/2.0)/PAIRSIZE)
#define MAXDINT (double)((HEAPSIZE/2.0)/DINTSIZE)

#endif
