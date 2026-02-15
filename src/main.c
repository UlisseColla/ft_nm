/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:13:08 by ucolla            #+#    #+#             */
/*   Updated: 2026/02/15 16:18:36 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/**
 * 1. Hande multiple files as argument.                     DONE
 * 2. Parser for the flags.                                 DONE
 * 3. Handle a.out if no arguments                          DONE
 * 4. Distinguish between 32 and 64 bits architecture       DONE
 * */

int main(int ac, char **av) {

    /* 1. Initial set up */
    Flags flags = {};
    t_list *files =  NULL;
    int status = 0;
    
    args_lexer(av, ac, &flags, &files);
    /* debug_prints(files, flags); */

    /* 2. Loop over files or a.out if no args */
    if (ft_lstsize(files) == 0) {
        file_info info = {};
        status = init_elf(&info, "./a.out");
        if (status == 1) return status; /* Cleaning to be done? */
    } else {
        for(int i = 0; i < ft_lstsize(files); files = files->next) {
            file_info info = {};
            status = init_elf(&info, files->content);
            if (status == 1) continue;
            
            status = ft_nm(&info, flags);
            if (files->next != NULL) write(1, "\n", 1);

            /* Remember to unmap the file! */
        }
    }
    
    clear_list(&files);
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