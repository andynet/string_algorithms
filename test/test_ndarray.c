#include <criterion/criterion.h>
#include "../lib/ndarray.h"
#include "../lib/ndarray.c"

Test(external, empty_test) {}

Test(internal, test_boundaries) {
    ndarray_t *ndarray = ndarray_create(3, 2, 3, 4);

    uint *p = ndarray_at(ndarray, 1, 2, 3);
    *p = 3;
    cr_assert(*p == ndarray->content[23]);
    p = ndarray_at(ndarray, 1, 2, 2);
    *p = 5;
    cr_assert(*p == ndarray->content[22]);
    p = ndarray_at(ndarray, 0, 0, 0);
    *p = 8;
    cr_assert(*p == ndarray->content[0]);

    ndarray_destroy(ndarray);
}

Test(external, ndarray_can_represent_2darray) {
    uint array[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    ndarray_t *ndarray = ndarray_create(2, 2, 3);
    uint *p;
    for (uint i = 0; i < 2; i++) {
        for (uint j = 0; j < 3; j++) {
            p = ndarray_at(ndarray, i, j);
            *p = array[i][j];
        }
    }

    for (uint i = 0; i < 2; i++) {
        for (uint j = 0; j < 3; j++) {
            p = ndarray_at(ndarray, i, j);
            cr_assert(*p == array[i][j]);
        }
    }

    ndarray_destroy(ndarray);
    ndarray = NULL;
}
