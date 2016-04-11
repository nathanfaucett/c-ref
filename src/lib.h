#ifndef __REF_H__
#define __REF_H__


#include "types/lib.h"
#include "thread/lib.h"

#define REF_VALUE(ref, type) ((type*) ref->value)

typedef void (*ref_destructor) (void* value);


extern void* malloc(uintsize size);
extern void free(void* ptr);


typedef struct Ref {
    Mutex mutex;
    void* value;
    ref_destructor destructor;
    uintsize count;
} Ref;

Ref* Ref_init(Ref* ref, void* value, ref_destructor destructor);
Ref* Ref_new(void* value, ref_destructor destructor);
void Ref_delete(Ref* ref);

void Ref_ref(Ref* ref);
bool Ref_deref(Ref* ref);


#endif
