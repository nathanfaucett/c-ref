#include <stdio.h>
#include <stdlib.h>

#include "../src/lib.h"


int main(void) {
    int32* value = malloc(sizeof(int32));
    *value = 8;

    Ref* ref = Ref_new(value, NULL);

    Ref_ref(ref);
    printf("%i\n", *REF_VALUE(ref, int));
    Ref_deref(ref);

    return 0;
}
