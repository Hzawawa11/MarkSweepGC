#ifndef BASIC_H
#define BASIC_H

#define TRUE 1
#define FALSE 0

#define car(o) (_PAIR(o,car))
#define cdr(o) (_PAIR(o,cdr))
#define rplaca(o, data) (_PAIR(o,car) = _DINT(data))
#define rplacd(o, data) (_PAIR(o,cdr) = _DINT(data))


/* basic.c */
Object* allocate(void);
Object* cons(Object* car, Object* cdr);
Object* atom(int i);


/*gc.c*/
void gc(void);
void RootScan(void);
void mark(void);
void sweep(void);
void state_Obj(Object* obj);
void state_list(void);
void init_free(void);
void init_gcs(void);
#define GCS_EMPTY() (stackpoint == 0)
int push_gcs(Object* obj);
Object* pop_gcs(void);

#endif
