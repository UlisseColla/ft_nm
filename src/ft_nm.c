/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:13:08 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/05 19:12:43 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int main(int ac, char **av) {
    
    if (ac != 2) {
        WRITE(ARGUMENTS_ERROR);
    }

    int fd = open(av[ac - 1], O_RDONLY, S_IWUSR | S_IRUSR);
    struct stat file_stat;
    
    if (fstat(fd, &file_stat) == -1) {
        perror("Couldn't get file size\n");
    }
    
    printf("File size is: %ld\n", file_stat.st_size);
    
    char *file_bytes = NULL;
    
    file_bytes = mmap(file_bytes, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (file_bytes == MAP_FAILED) {
        strerror(errno);
        return -1;
    }

    elf_h *elf_header = (elf_h *)file_bytes;
    print_ekh_header(elf_header);

    sec_h *sec_header = (sec_h *)file_bytes + elf_header->e_shoff - 1;
    print_sec_header(sec_header);

    return 0;
}


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