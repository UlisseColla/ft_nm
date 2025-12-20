# include <ft_nm.h>
#include <string.h>

static int partition(symbols_t array[], int lower, int higher)
{
    symbols_t pivot = array[higher];
    int i = (lower - 1);

    for (int j = lower; j < higher; j++) {
        int cmp = ft_nm_strcmp(array[j].name, pivot.name);
        if (cmp < 0 || (cmp == 0 && (
            (array[j].type == 't' && pivot.type == 'T') ||
            (array[j].value < pivot.value && array[j].type != 'T') ||
            (array[j].value == pivot.value && (array[j].type < pivot.type) && !(array[j].name[0] == '_' && pivot.name[0] == '.')) ||
            (array[j].value == pivot.value && (array[j].type != 'W' && array[j].type != 'w') && !(array[j].name[0] == '_' && pivot.name[0] == '.'))
            ))) {
            i++;
            symbols_t temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    symbols_t temp = array[i + 1];
    array[i + 1] = array[higher];
    array[higher] = temp;
    return (i + 1);
}

void quick_sort(symbols_t array[], int lower, int higher)
{
    if (lower < higher) {
        int pivot = partition(array, lower, higher);

        quick_sort(array, lower, pivot - 1);
        quick_sort(array, pivot + 1, higher);
    }
}
