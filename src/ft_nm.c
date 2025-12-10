/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:13:08 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/10 12:57:29 by ucolla           ###   ########.fr       */
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

    elf_h *elf_header = (elf_h *)file_bytes;
    print_ekh_header(elf_header);

    uint32_t str_tab_index = 0;
    sym_h *symbol_array = NULL;
    int symbols_count = 0;

    sec_h *sec_header = (sec_h *)(file_bytes + elf_header->e_shoff);
    sec_h *sh_symtab = NULL;
    for (int i = 0; i < elf_header->e_shnum; i++) {
        switch(sec_header[i].sh_type) {
            case SHT_SYMTAB:
                printf("SECTION SHT_SYMTAB %d\n", i);
                print_sec_header(&sec_header[i]);
                str_tab_index = sec_header[i].sh_link;
                symbol_array = (sym_h *)(file_bytes + sec_header[i].sh_offset);
                symbols_count = sec_header[i].sh_size / sizeof(sym_h);
                sh_symtab = &sec_header[i];
                printf("\n");
                break;
                
            case SHT_STRTAB:
                printf("SECTION SHT_STRTAB %d\n", i);
                print_sec_header(&sec_header[i]);
                printf("\n");
                break;

            case SHT_DYNSYM:
                printf("SECTION SHT_DYNSYM %d\n", i);
                print_sec_header(&sec_header[i]);
                printf("\n");
                break;
                
            default: break;
        }
    }

    char *str_table_data = (char *)(file_bytes + sec_header[str_tab_index].sh_offset);
    
    printf("sec_header[i].sh_size: %ld - sizeof(sym_h): %ld\n", sh_symtab->sh_size, sizeof(sym_h));
    printf("Total symbols found: %d\n\n", symbols_count);
    
    for(int i = 0; i < symbols_count; i++) {
        uint32_t offset = symbol_array[i].st_name;
        uint64_t value = symbol_array[i].st_value;
        uint8_t info = ELF64_ST_TYPE(symbol_array[i].st_info);

        if (offset != 0) {
            if (value != 0) {
                printf("%lx - ", value);
            }
            printf("info: %x - %s\n", info, str_table_data + offset);
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