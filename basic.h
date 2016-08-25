#ifndef BASIC_H
#define BASIC_H

#define TRUE 1
#define FALSE 0

#define car(o) (o->Pair.car)
#define cdr(o) (o->Pair.cdr)
#define rplaca(o, data) (car(o) = data)
#define rplacd(o, data) (cdr(o) = data)


/* basic.c */
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
#define GCS_EMPTY() (stackpoint == 0)
void init_gcs(void);
int push_gcs(Object* obj);
Object* pop_gcs(void);
void init_local(void);
int push_local(Object* obj);
Object* pop_local(void);

#endif
