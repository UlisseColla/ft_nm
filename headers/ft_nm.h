/* ************************************************************************** */
/*                                                                            */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                        :::      ::::::::   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:07:11 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/21 18:17:13 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
#define FT_NM_H

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ft_printf_fd.h"
#include "libft.h"
#include "./elf.h"

typedef enum architecture {
    ARCH_32, ARCH_64 
}   Arch;

typedef enum lexer_status {
    FLAG, FILENAME, ERROR 
}   Status;

typedef enum sorting {
    ALPHA, REVERSE, UNSORTED 
}   Sort;

typedef enum filter {
    DEFAULT, ALL, EXTERNAL, UNDEFINED
}   Filter;

typedef struct s_flags {
    Filter  filter;
    Sort    sort;
}   Flags;

/* 64 BITS */
typedef Elf64_Ehdr elf_64;
typedef Elf64_Shdr sec_64;
typedef Elf64_Sym sym_64;
/* 32 BITS */
typedef Elf32_Ehdr elf_32;
typedef Elf32_Shdr sec_32;
typedef Elf32_Sym sym_32;

typedef struct s_file_info {
    char *file_name;
    char *elf_file;
    size_t file_size;
    Arch arch;
}   file_info;

typedef struct s_symbol {
    char *name;
    char *address;
    char type;
    unsigned char info;
}   symbol;

#define SUCCESS 0
#define FAILURE 1

#define ARGUMENTS_ERROR     "Usage: nm [option(s)] [file(s)]\n \
List symbols in [file(s)] (a.out by default).\n \
The options are:\n \
-a,     Display also debugger-only symbols\n \
-g,     Display only external symbols\n \
-u,     Display only undefined symbols\n \
-r,     Reverse the sense of the sort\n \
-p,     Do not sort the symbols\n\n"

void print_ekh_header(elf_64 *ekh);
void print_sec_64eader(sec_64 *header);
void debug_prints(t_list *files, Flags flags);
void print_line(symbol s);
void args_lexer(char **av, int ac, Flags *flags, t_list **files);
char *get_address(uint64_t addr, char flag);
char set_flag(sym_64 *sym, sec_64 *sections, void *max);
void clear_list(t_list **list);
int ft_nm(file_info *info, Flags flags);
int init_elf(file_info *info, char *file_path);

int compare_strings(char *s1, char *s2);
void swap_symbols(symbol *sym1, symbol *sym2);
void quick_sort(symbol *array, int low, int high);

void print_symbols(int size, symbol *array, Flags flags);
void print_symbols_r(int size, symbol *array, Flags flags);

// void quick_sort_int(int array[], int low, int high);

#endif
