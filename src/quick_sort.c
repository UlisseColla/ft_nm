/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:57:35 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/18 19:21:35 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/**
 * skip _ and case insensitive.
 * If result is negative, s1 comes before s2, and viceversa.
 * If 0 they are equal.
 */
int compare_strings(char *s1, char *s2) {
    if (!s1 || !s2) return -1;

    int i, l;
    i = 0, l = 0;
    
    while(s1 && s2 && s1[i] == s2[l]) {
        while(s1 && s1[i] == '_') i++;
        while(s2 && s2[l] == '_') l++;
        if (s1[i] != s2[l]) break;
        i++;
        l++;
    }
    return s1[i] - s2[l];
}

void swap_symbols(symbol *sym1, symbol *sym2) {
    if (!sym1 || !sym2) return;
    if (sym1 == sym2) return;

    symbol swap = *sym1;
    *sym1 = *sym2;
    *sym2 = swap;
}

int partition(symbol *array, int low, int high) {
    char *pivot = array[low].name;
    int leftwall = low;
    
    for(int i = low + 1; i <= high; i++) {
        int cmp = compare_strings(array[i].name, pivot);
        if (cmp < 0) {
            leftwall++;
            swap_symbols(&array[i], &array[leftwall]);
        }
    }
    swap_symbols(&array[low], &array[leftwall]);

    return leftwall;
}

void quick_sort(symbol *array, int low, int high) {
    if (low < high) {
        int pivot_location = partition(array, low, high);
        
        quick_sort(array, low, pivot_location - 1);
        quick_sort(array, pivot_location + 1, high);
    }
}

/**
 *  Partition(A as array, low as int, high as int){
        pivot = A[low]
        leftwall = low

        for i = low + 1 to high {
            if (A[i] < pivot) then {
                swap(A[i], A[leftwall + 1])
                leftwall = leftwall + 1
            }
        }
        swap(pivot,A[leftwall])

        return (leftwall)
    }
 *  Quicksort(A as array, low as int, high as int){
        if (low < high){
            pivot_location = Partition(A,low,high)
            Quicksort(A,low, pivot_location-1)
            Quicksort(A, pivot_location + 1, high)
        }
    }
 */

/* int partition_int(int array[], int low, int high) {
    int pivot = array[low];
    int leftwall = low;

    for(int i = low + 1; i <= high; i++) {
        if (array[i] < pivot) {
            leftwall++;
            int temp = array[i];
            array[i] = array[leftwall];
            array[leftwall] = temp;
        }
    }
    int temp1 = array[low];
    array[low] = array[leftwall];
    array[leftwall] = temp1;

    printf("    Leftwall: %d\n", leftwall);
    return leftwall;
}
void quick_sort_int(int array[], int low, int high) {
    static int counter = 0;
    counter++;

    printf("Iteration n.%d\n", counter);
    if (low < high) {
        int pivot_location = partition_int(array, low, high);
        
        quick_sort_int(array, low, pivot_location - 1);
        quick_sort_int(array, pivot_location + 1, high);
    }
} */
