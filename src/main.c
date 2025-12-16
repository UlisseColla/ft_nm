/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:13:08 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/16 19:08:20 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/**
 * 1. Hande multiple files as argument.                     DONE
 * 2. Parser for the flags.                                 DONE
 * 3. Handle a.out if no arguments
 * 4. Distinguish between 32 and 64 bits architecture       DONE
 * */

int main(int ac, char **av) {

    /* 1. Initial set up */
    Flags flags = {};
    t_list *files =  NULL;
    int status = 0;
    
    args_lexer(av, ac, &flags, &files);
    /* debug_prints(files, flags); */

    /* 2. Loop over files */
    if (ft_lstsize(files) == 0) {
        
    }
    for(int i = 0; i < ft_lstsize(files); files = files->next) {
        file_info info = {};
        status = init_elf(&info, files->content);
        if (status == 1) {
            clear_list(&files);
            return 1;
        }

        
        
    }
    
    /* Total amount of symbols */
    uint32_t str_tab_index = 0;

    /* Array of symbols */
    sym_64 *symbol_array = NULL;
    int symbols_count = 0;

    /* e. get the sections header's table, i.e the array of section headers */
    sec_64 *sec_headers = (sec_64 *)(file_bytes + elf_64eader->e_shoff);
    
    for (int i = 0; i < elf_64eader->e_shnum; i++) {
        switch(sec_64eader[i].sh_type) {
            case SHT_SYMTAB:
                str_tab_index = sec_64eader[i].sh_link;
                symbol_array = (sym_64 *)(file_bytes + sec_64eader[i].sh_offset);
                symbols_count = sec_64eader[i].sh_size / sizeof(sym_64);
                break;
                
            case SHT_STRTAB:
                break;

            case SHT_DYNSYM:
                break;
                
            default: break;
        }
    }

    /* String table to find the actual string for the symbols */
    char *str_table_data = (char *)(file_bytes + sec_64eader[str_tab_index].sh_offset);

    symbol *total_symbols = (symbol *)malloc(symbols_count * (sizeof(symbol)));

    /* Loop through symbols */
    int l = 0;
    for(int i = 0; i < symbols_count; i++) {
        uint32_t offset = symbol_array[i].st_name;
        uint64_t value = symbol_array[i].st_value;
        char *addr = NULL;
        char flag;

        if (offset != 0 && (void *)&sec_64eader[symbol_array[i].st_shndx] < (void *)file_bytes + file_size) {            
            flag = set_flag(&symbol_array[i], sec_64eader, (file_bytes + file_size));
            addr = get_address(value, flag);
            // printf(" - %s\n", str_table_data + offset);
            
            symbol new = {str_table_data + offset, addr, flag};
            total_symbols[l] = new;
            l++;
        }
    }
    // printf("\n");

    for(int i = 0; i < symbols_count; i++) {
        print_line(total_symbols[i]);
    }

    return status;
}

/*
    typedef struct {
        unsigned char e_ident[EI_NIDENT];
        uint16_t      e_type;
        uint16_t      e_machine;
        uint32_t      e_version;
        ElfN_Addr     e_entry;
        ElfN_Off      e_phoff;
        ElfN_Off      e_shoff;
        uint32_t      e_flags;
        uint16_t      e_ehsize;
        uint16_t      e_phentsize;
        uint16_t      e_phnum;
        uint16_t      e_shentsize;
        uint16_t      e_shnum;
        uint16_t      e_shstrndx;
    } ElfN_Ehdr;
*/

/*
    typedef struct {
        uint32_t      st_name;
        unsigned char st_info;
        unsigned char st_other;
        uint16_t      st_shndx;
        Elf64_Addr    st_value;
        uint64_t      st_size;
    } Elf64_Sym; 
 */

/* 
    typedef struct {
        uint32_t   sh_name;
        uint32_t   sh_type;
        uint64_t   sh_flags;
        Elf64_Addr sh_addr;
        Elf64_Off  sh_offset;
        uint64_t   sh_size;
        uint32_t   sh_link;
        uint32_t   sh_info;
        uint64_t   sh_addralign;
        uint64_t   sh_entsize;
    } Elf64_Shdr; 
*/