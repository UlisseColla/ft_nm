/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:13:08 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/10 19:30:31 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/**
 * 1. Hande multiple files as argument.                     DONE
 * 2. Parser for the flags.                                 DONE
 * 3. Handle a.out if no arguments
 * 4. Distinguish between 32 and 64 bits architecture       DONE
 * */

 void debug_prints(t_list *files, Flags flags) {
    while(files->next) {
        printf("File is: %s\n", (char *)files->content);
        files = files->next;
    }
    printf("File is: %s\n\n", (char *)files->content);
    printf("Flag are - sort: %d - filter: %d\n", flags.sort, flags.filter);
 }

int main(int ac, char **av) {

    /* Initial set up */
    /* Arch arch = (sizeof(void *) * 8) == 64 ? ARCH_64 : ARCH_32;

    Flags flags = {};

    t_list *files =  NULL;
    args_lexer(av, ac, &flags, &files);

    debug_prints(files, flags); */
    
    int fd = open(av[ac - 1], O_RDONLY, S_IWUSR | S_IRUSR);
    if (fd == -1) {
        ft_printf("nm: \'%s\' : %s\n", av[ac - 1], strerror(errno));
        exit(1);
    }
    
    struct stat file_stat;
    
    if (fstat(fd, &file_stat) == -1) {
        perror("Couldn't get file size\n");
    }
    
    printf("File size is: %ld\n\n", file_stat.st_size);
    
    char *file_bytes = NULL;
    
    file_bytes = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (file_bytes == MAP_FAILED) {
        perror("Error when mapping the file\n");
        return -1;
    }

    /* ELF header */
    elf_h *elf_header = (elf_h *)file_bytes;
    print_ekh_header(elf_header);

    
    /* Total amount of symbols */
    uint32_t str_tab_index = 0;

    /* Array of symbols */
    sym_h *symbol_array = NULL;
    int symbols_count = 0;

    /* Sections header's table, i.e the array of section headers */
    sec_h *sec_header = (sec_h *)(file_bytes + elf_header->e_shoff);

    /* Section with sections names */
    sec_h *sh_str_tab = NULL;
    int sh_str_tab_index;

    /* Symbol table sh */
    sec_h *sh_symtab = NULL;
    
    for (int i = 0; i < elf_header->e_shnum; i++) {
        switch(sec_header[i].sh_type) {
            case SHT_SYMTAB:
                printf("SECTION SHT_SYMTAB %d\n", i);
                print_sec_header(&sec_header[i]);
                printf("\n");
                
                str_tab_index = sec_header[i].sh_link;
                symbol_array = (sym_h *)(file_bytes + sec_header[i].sh_offset);
                symbols_count = sec_header[i].sh_size / sizeof(sym_h);
                sh_symtab = &sec_header[i];
                
                break;
                
            case SHT_STRTAB:
                printf("SECTION SHT_STRTAB %d\n", i);
                print_sec_header(&sec_header[i]);
                printf("\n");

                sh_str_tab = &sec_header[i];
                sh_str_tab_index = sec_header[i].sh_link;

                break;

            case SHT_DYNSYM:
                printf("SECTION SHT_DYNSYM %d\n", i);
                print_sec_header(&sec_header[i]);
                printf("\n");
                break;
                
            default: break;
        }
    }

    /* String table to find the actual string for the symbols */
    char *str_table_data = (char *)(file_bytes + sec_header[str_tab_index].sh_offset);
    char *str_table_section_names = (char *)(file_bytes + sec_header[sh_str_tab_index].sh_offset);
    
    printf("Total symbols found: %d\n\n", symbols_count);
    
    /* Loop through symbols */
    for(int i = 0; i < symbols_count; i++) {
        uint32_t offset = symbol_array[i].st_name;
        uint64_t value = symbol_array[i].st_value;
        uint16_t shndx = symbol_array[i].st_shndx;
        uint8_t info = ELF64_ST_TYPE(symbol_array[i].st_info);
        char *section_name;

        char flag;

        flag = set_flag(info, shndx);
        (void)flag;
        
        /* section_name = str_table_section_names */ /* To be finished */

        if (offset != 0) {
            if (value != 0) {
                char *addr = get_address(value);
                for (int i = 0; i < (16 - (int)ft_strlen(addr)); i++) {
                    write(1, "0", 1);
                }
                printf("%s ", addr);
            }
            printf("%s\n", str_table_data + offset);
            printf("shndx: %d\n\n", shndx);
        }
    }

    close(fd);

    return 0;
}

/*
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
*/