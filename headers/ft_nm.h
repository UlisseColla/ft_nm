/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:07:11 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/10 18:39:26 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
#define FT_NM_H

#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <elf.h>
#include "libft.h"
#include "ft_printf.h"

typedef enum architecture {
    ARCH_32, ARCH_64 
}   Arch;

typedef enum lexer_status {
    OK, FILENAME, ERROR 
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

typedef Elf64_Ehdr elf_h;
typedef Elf64_Shdr sec_h;
typedef Elf64_Sym sym_h;

typedef struct s_symbol {
    char *name;
    char *address;
    char type;
}   symbol;

#define ARGUMENTS_ERROR     "Usage: nm [option(s)] [file(s)]\n \
List symbols in [file(s)] (a.out by default).\n \
The options are:\n \
-a,     Display debugger-only symbols\n \
-g,     Display only external symbols\n \
-u,     Display only undefined symbols\n \
-r,     Reverse the sense of the sort\n \
-p,     Do not sort the symbols\n\n"

void print_ekh_header(elf_h *ekh);
void print_sec_header(sec_h *header);
void args_lexer(char **av, int ac, Flags *flags, t_list **files);
char *get_address(uint64_t addr);
char set_flag(uint8_t info, uint16_t shndx);

#endif
