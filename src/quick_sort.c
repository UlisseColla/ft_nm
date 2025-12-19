/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:57:35 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/19 14:16:27 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static inline char to_lower(char c) {
    return c >= 'A'&& c <= 'Z'? c + 32 : c;
}

/**
 * skip _ and case insensitive.
 * If result is negative, s1 comes before s2, and viceversa.
 * If 0 they are equal.
 */
int compare_strings(char *s1, char *s2) {
    if (!s1 || !s2) return -1;

    int i = 0;
    int l = 0;
    char *c1 = s1;
    char *c2 = s2;
    
    while(c1[i] && c2[l]) {
        while(c1[i] && c1[i] == '_') i++;
        while(c2[l] && c2[l] == '_') l++;
        if (to_lower(c1[i]) != to_lower(c2[l])) break;
        i++;
        l++;
    }
    return to_lower(c1[i]) - to_lower(c2[l]);
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
