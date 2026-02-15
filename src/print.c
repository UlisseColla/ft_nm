/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:18:32 by ucolla            #+#    #+#             */
/*   Updated: 2026/02/15 17:22:23 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/* void debug_prints(t_list *files, Flags flags) {
    while(files->next) {
        printf("File is: %s\n", (char *)files->content);
        files = files->next;
    }
    printf("File is: %s\n\n", (char *)files->content);
    printf("Flag are - sort: %d - filter: %d\n", flags.sort, flags.filter);
} */

static void print_line(symbol s, Arch arch) {
    int format = arch == ARCH_32? 8 : 16;
    if (s.name == NULL || ft_strlen(s.name) == 0) return;
    if (s.address != NULL) {
        for (int i = 0; i < (format - (int)ft_strlen(s.address)); i++) {
            write(1, "0", 1);
        }
        ft_printf_fd(1, "%s", s.address);
    } else {
        for(int i = 0; i < format; i++) {
            write(1, " ", 1);
        }
    }
    ft_printf_fd(1, " %c ", s.type);
    ft_printf_fd(1, "%s\n", s.name);
}

void print_symbols(int size, symbol *array, Flags flags, Arch arch) {
    switch(flags.filter) {
        case UNDEFINED:
            for(int i = 0; i < size; i++) {
                if (array[i].type == 'U') print_line(array[i], arch);
            };
            break;
        case EXTERNAL:
            for(int i = 0; i < size; i++) {
                uint8_t bind = ELF64_ST_BIND(array[i].info);
                if (bind == STB_GLOBAL || bind == STB_WEAK) print_line(array[i], arch);
            };
            break;
        case ALL:
            for(int i = 0; i < size; i++) {
                print_line(array[i], arch);
            };
            break;
        default:
            for(int i = 0; i < size; i++) {
                if (array[i].type == 'a' || array[i].type == 'A') continue;
                print_line(array[i], arch);
            };
            break;
    }
}

void print_symbols_r(int size, symbol *array, Flags flags, Arch arch) {
    switch(flags.filter) {
        case UNDEFINED:
            for(int i = size - 1; i >= 0; i--) {
                if (array[i].type == 'U') print_line(array[i], arch);
            };
            break;
        case EXTERNAL:
            for(int i = size - 1; i >= 0; i--) {
                uint8_t bind = ELF64_ST_BIND(array[i].info);
                if (bind == STB_GLOBAL || bind == STB_WEAK) print_line(array[i], arch);
            };
            break;
        case ALL:
            for(int i = size - 1; i >= 0; i--) {
                print_line(array[i], arch);
            };
            break;
        default:
            for(int i = size - 1; i >= 0; i--) {
                if (array[i].type == 'a' || array[i].type == 'A') continue;
                print_line(array[i], arch);
            };
            break;
    }
}
