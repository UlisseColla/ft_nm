/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:47:25 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/17 17:26:20 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char *get_address(uint64_t addr, char flag) {
    uint8_t buf[16];
    char ret[16];
    char base[] = "0123456789abcdef";
    int l = 0;
    int i = 0;

    if (flag == 'U' || flag == 'w') return NULL;
    if (addr == 0) {
        return ft_strdup("0000000000000000");
    }
    
    while(addr) {
        buf[i] = addr % 16;
        addr /= 16;
        i++;
    }
    
    i--;
    while(i >= 0) {
        ret[l] = base[buf[i]];
        l++;
        i--;
    }
    ret[l] = '\0';
    
    return ft_strdup(ret);
}

int check_arch(unsigned char *e_ident, file_info *info) {
    if (e_ident[EI_MAG0] != ELFMAG0 ||
        e_ident[EI_MAG1] != ELFMAG1 ||
        e_ident[EI_MAG2] != ELFMAG2 ||
        e_ident[EI_MAG3] != ELFMAG3) {
            write(2, "Wrongly formatted or corrupted ELF ident\n", 41);
            return 1;
        }
    
    switch(e_ident[EI_CLASS]) {
        case ELFCLASS32:
            info->arch = ARCH_32;
            break;
        case ELFCLASS64:
            info->arch = ARCH_64;
            break;
        default:
            write(2, "Invalid elf class, neither 64 bits nor 32 bits\n", 47);
            return 1;
    }
    return 0;
}

int init_elf(file_info *info, char *file_path) {
    struct stat file_stat;
    int fd = open(file_path, O_RDONLY, S_IWUSR | S_IRUSR);
    char *file_bytes = NULL;
    int ret = 0;
    
    if (fd == -1) {
        ft_printf("nm: \'%s\' : %s\n", file_path, strerror(errno));
        close(fd);
        return 1;
    }
    info->file_name = file_path;
    if (fstat(fd, &file_stat) == -1) {
        perror("Couldn't get file size\n");
        close(fd);
        return 1;
    }
    info->file_size = file_stat.st_size;
    
    file_bytes = mmap(NULL, info->file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (file_bytes == MAP_FAILED) {
        perror("Error when mapping the file\n");
        close(fd);
        return 1;
    }
    info->elf_file = file_bytes;
    close(fd);

    ret = check_arch((unsigned char *)file_bytes, info);
    
    return ret;
}
