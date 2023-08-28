#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
typedef short int16_t;
#define ARRAY_CREATE(array, init_capacity, init_size)                 \
    {                                                                 \
        array = malloc(sizeof(*array));                               \
        array->data = malloc((init_capacity) * sizeof(*array->data)); \
        assert(array->data != NULL);                                  \
        array->capacity = init_capacity;                              \
        array->size = init_size;                                      \
    }
#define ARRAY_PUSH(array, item)                                                         \
    {                                                                                   \
        if (array->size == array->capacity)                                             \
        {                                                                               \
            array->capacity *= 2;                                                       \
            array->data = realloc(array->data, array->capacity * sizeof(*array->data)); \
            assert(array->data != NULL);                                                \
        }                                                                               \
        array->data[array->size++] = item;                                              \
    }

struct array_number_t
{
    int16_t size;
    int16_t capacity;
    int16_t *data;
};

static struct array_number_t *arr;
static int16_t i;
int main(void)
{
    ARRAY_CREATE(arr, 2, 0);
    ARRAY_PUSH(arr, 23);
    ARRAY_PUSH(arr, 234);
    printf("[ ");
    for (i = 0; i < arr->size; i++)
    {
        if (i != 0)
            printf(", ");
        printf("%d", arr->data[i]);
    }
    printf(" ]\n");
    free(arr->data);
    free(arr);

    return 0;
}
