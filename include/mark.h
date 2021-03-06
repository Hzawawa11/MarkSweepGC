#ifndef MARK_H
#define MARK_H

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
void init_gcs(void);
int push_gcs(Object* obj);
Object* pop_gcs(void);
void init_local(void);
int push_local(Object* obj);
Object* pop_local(void);

#endif
