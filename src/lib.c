#ifndef __REF_C__
#define __REF_C__


#include "./lib.h"
#include "thread/lib.c"


Ref* Ref_init(Ref* ref, void* value, ref_destructor destructor) {
    Mutex_init(&ref->mutex, mutex_plain);
    ref->value = value;
    ref->count = 0;
    ref->destructor = destructor;
    return ref;
}
Ref* Ref_new(void* value, ref_destructor destructor) {
    return Ref_init((Ref*) malloc(sizeof(Ref)), value, destructor);
}
void Ref_delete(Ref* ref) {
    Mutex_destroy(&ref->mutex);
    if (ref->destructor != NULL) {
        ref->destructor(ref->value);
    }
    free(ref->value);
    free(ref);
}

void Ref_ref(Ref* ref) {
    Mutex_lock(&ref->mutex);
    ref->count++;
    Mutex_unlock(&ref->mutex);
}
bool Ref_deref(Ref* ref) {
    Mutex_lock(&ref->mutex);
    ref->count--;
    Mutex_unlock(&ref->mutex);

    if (ref->count == 0) {
        Ref_delete(ref);
        return true;
    } else {
        return false;
    }
}


#endif
