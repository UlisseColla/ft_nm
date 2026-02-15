/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:29:31 by ucolla            #+#    #+#             */
/*   Updated: 2026/02/15 15:55:12 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/* void free_array(void *array, size_t size) {
    if (array == NULL || size <= 0) return;
    size_t i = 0;
    while(i < size) {
        free(array);
        array++;
        array = NULL;
        i++;
    }
} */

int ft_nm(file_info *info, Flags flags) {
    
    int symbols_count = 0;
    symbol *sym_struct_array = NULL;
    
    #define PROCESS_ELF(base) \
        elf_ ## base *header = (elf_ ## base *)info->elf_file; \
        sec_ ## base *sec_headers = (sec_ ## base *)(info->elf_file + header->e_shoff); \
        sym_ ## base *symbol_array = NULL; \
        uint32_t str_tab_index = 0; \
        \
        for (int i = 0; i < header->e_shnum; i++) { \
            if (sec_headers[i].sh_type == SHT_SYMTAB) { \
                str_tab_index = sec_headers[i].sh_link; \
                symbol_array = (sym_ ## base *)(info->elf_file + sec_headers[i].sh_offset); \
                symbols_count = sec_headers[i].sh_size / sizeof(sym_ ## base); \
                break; \
            } \
        } \
        \
        if (symbol_array) { \
            char *str_table_data = (char *)(info->elf_file + sec_headers[str_tab_index].sh_offset); \
            sym_struct_array = (symbol *)malloc(symbols_count * (sizeof(symbol))); \
            \
            int l = 0; \
            for(int i = 0; i < symbols_count; i++) { \
                uint32_t offset = symbol_array[i].st_name; \
                uint64_t value = symbol_array[i].st_value; \
                uint16_t shndx = symbol_array[i].st_shndx; \
                char *addr = NULL; \
                char flag; \
                \
                int is_special = (shndx == SHN_ABS || shndx == SHN_COMMON || shndx == SHN_UNDEF); \
                int is_valid_section = (shndx < header->e_shnum); \
                \
                if (is_special || is_valid_section) { \
                    flag = set_flag(&symbol_array[i], sec_headers, info->elf_file + info->file_size, info->arch); \
                    addr = get_address(value, flag, info->arch); \
                    \
                    symbol new = {str_table_data + offset, addr, flag, symbol_array[i].st_info}; \
                    sym_struct_array[l] = new; \
                    l++; \
                } \
            } \
            symbols_count = l; \
        }

    if (info->arch == ARCH_32) {
        PROCESS_ELF(32)
    } else {
        PROCESS_ELF(64)
    }

    #undef PROCESS_ELF
    
    if (!sym_struct_array) return 0;

    if (flags.sort != UNSORTED) quick_sort(sym_struct_array, 0, symbols_count - 1);

    return 0;
}