/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:29:31 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/22 17:46:07 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void free_array(void *array, size_t size) {
    if (array == NULL || size <= 0) return;
    size_t i = 0;
    while(i < size) {
        free(array);
        array++;
        array = NULL;
        i++;
    }
}

int ft_nm(file_info *info, Flags flags) {
    /* Total amount of symbols */
    uint32_t str_tab_index = 0;
    uint32_t dyn_tab_index = 0;
    uint32_t sht_strtab_index = 0;

    /* Array of symbols */
    sym_64 *symbol_array = NULL;
    int symbols_count = 0;
    
    sym_64 *dyn_sym_array = NULL;
    int dyn_sym_count = 0;
    
    elf_64 *header = (elf_64 *)info->elf_file;
    
    sec_64 *sec_headers = (sec_64 *)(info->elf_file + header->e_shoff);
    for (int i = 0; i < header->e_shnum; i++) {
        switch(sec_headers[i].sh_type) {
            case SHT_SYMTAB:
                str_tab_index = sec_headers[i].sh_link;
                symbol_array = (sym_64 *)(info->elf_file + sec_headers[i].sh_offset);
                symbols_count = sec_headers[i].sh_size / sizeof(sym_64);
                break;
                
            case SHT_STRTAB:
                sht_strtab_index = sec_headers[i].sh_link;
                break;

            case SHT_DYNSYM:
                dyn_tab_index = sec_headers[i].sh_link;
                dyn_sym_array = (sym_64 *)(info->elf_file + sec_headers[i].sh_offset);
                dyn_sym_count = sec_headers[i].sh_size / sizeof(sym_64);
                break;
                
            default: break;
        }
    }
    
    char *str_table_data = (char *)(info->elf_file + sec_headers[str_tab_index].sh_offset);
    symbol *sym_struct_array = (symbol *)malloc(symbols_count * (sizeof(symbol)));

    char *dyn_str_table = (char *)(info->elf_file + sec_headers[dyn_tab_index].sh_offset);

    // char *sec_strtab = (char *)(info->elf_file + sec_headers[sht_strtab_index].sh_offset);

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

    if (flags.sort != UNSORTED) quick_sort(sym_struct_array, 0, symbols_count - 1);

    
    for (int i = 0; i < header->e_shnum; i++) {
        int offset = sec_headers[i].sh_name;
        printf("Section is: %s\n", (char *)(info->elf_file + sec_headers[sht_strtab_index].sh_offset + offset));
    }

    /* if (flags.sort == REVERSE) {
        print_symbols_r(symbols_count, sym_struct_array, flags);
    } else {
        print_symbols(symbols_count, sym_struct_array, flags);
    } */

    printf("\nDynanmic symbols section\n");
    printf("Count: %d\n", dyn_sym_count);
    for (int i = 0; i < dyn_sym_count; i++) {
        printf("Symbol: %s\n", dyn_str_table + dyn_sym_array[i].st_name);
    }

    free_array((void *)sym_struct_array, symbols_count);
    return 0;
}