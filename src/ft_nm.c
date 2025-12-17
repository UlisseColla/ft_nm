/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:29:31 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/17 18:57:51 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/* 
typedef struct s_file_info {
    char *file_name;
    char *elf_file;
    size_t file_size;
    Arch arch;
}   file_info;
*/

void free_array(void **array, size_t size) {
    if (array == NULL || size <= 0) return;
    for (int i = 0; i < size; i++) {
        free(array[i]);
        array[i] = NULL;
    }
}

int ft_nm(file_info *info, Flags flags) {
    /* Total amount of symbols */
    uint32_t str_tab_index = 0;

    /* Array of symbols */
    sym_64 *symbol_array = NULL;
    int symbols_count = 0;

    elf_64 *header = (elf_64 *)info->elf_file;
    /* Checks on elf header's values */
    
    sec_64 *sec_headers = (sec_64 *)(info->elf_file + header->e_shoff);
    for (int i = 0; i < header->e_shnum; i++) {
        switch(sec_headers[i].sh_type) {
            case SHT_SYMTAB:
                str_tab_index = sec_headers[i].sh_link;
                symbol_array = (sym_64 *)(info->elf_file + sec_headers[i].sh_offset);
                symbols_count = sec_headers[i].sh_size / sizeof(sym_64);
                break;
                
            case SHT_STRTAB:
                break;

            case SHT_DYNSYM:
                break;
                
            default: break;
        }
    }
    
    char *str_table_data = (char *)(info->elf_file + sec_headers[str_tab_index].sh_offset);
    symbol *sym_struct_array = (symbol *)malloc(symbols_count * (sizeof(symbol)));

    /* Loop through symbols */
    int l = 0;
    for(int i = 0; i < symbols_count; i++) {
        uint32_t offset = symbol_array[i].st_name;
        uint64_t value = symbol_array[i].st_value;
        char *addr = NULL;
        char flag;

        if (offset != 0 && (void *)&sec_headers[symbol_array[i].st_shndx] < (void *)info->elf_file + info->file_size) {            
            flag = set_flag(&symbol_array[i], sec_headers, info->elf_file + info->file_size);
            addr = get_address(value, flag);
            
            symbol new = {str_table_data + offset, addr, flag};
            sym_struct_array[l] = new;
            l++;
        }
    }

    for(int i = 0; i < symbols_count; i++) {
        /* Flags to be used in here */
        (void)flags;
        print_line(sym_struct_array[i]);
    }

    free_array(&sym_struct_array, symbols_count);
    return 0;
}