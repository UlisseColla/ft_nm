/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:47:25 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/21 18:13:52 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char *get_address(uint64_t addr, char flag) { /* To check for 32 bits arch */
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

/* Check all sizes, if bigger than file size -> print error, return 1 */
/*
typedef struct s_file_info {
    char *file_name;
    char *elf_file;
    size_t file_size;
    Arch arch;
}   file_info;
*/

/*
    typedef struct {
        unsigned char e_ident[EI_NIDENT];   ok
        uint16_t      e_type;
        uint16_t      e_machine;            ok
        uint32_t      e_version;
        ElfN_Addr     e_entry;
        ElfN_Off      e_phoff;              ok
        ElfN_Off      e_shoff;              ok
        uint32_t      e_flags;
        uint16_t      e_ehsize;             ok
        uint16_t      e_phentsize;
        uint16_t      e_phnum;
        uint16_t      e_shentsize;          ok
        uint16_t      e_shnum;
        uint16_t      e_shstrndx;
    } ElfN_Ehdr;
*/
static int check_elf(file_info *info) {
    
    /* Check for leaks in get_address */
    #define CHECK_ELF_HEADER(base)                                                                                                                      \
            size_t ehsize_std = base == 64? 64 : 52;                                                                                                    \
            elf_ ## base *header = (elf_ ## base *)info->elf_file;                                                                                      \
            if (header->e_phoff > info->file_size) {                                                                                                    \
                return ft_printf_fd(2, "Program header offset goes past the end of the file: e_phoff = 0x%s\n", get_address(header->e_phoff, '-'));     \
            }                                                                                                                                           \
            if (header->e_shoff > info->file_size) {                                                                                                    \
                return ft_printf_fd(2, "Section header table goes past the end of the file: e_shoff = 0x%s\n", get_address(header->e_shoff, '-'));      \
            }                                                                                                                                           \
            if (header->e_ehsize != ehsize_std) {                                                                                                       \
                return ft_printf_fd(2, "ft_nm: %s: File format not recognized\n", info->file_name);                                                     \
            }                                                                                                                                           \
            if (header->e_shentsize != sizeof(sec_ ## base)) {                                                                                          \
                return ft_printf_fd(2, "Invalid e_shentsize in ELF header: %s\n", ft_itoa(header->e_shentsize));                                        \
            }                                                                                                                                           \
            if (header->e_version == EV_NONE || !header->e_shnum || !header->e_shoff ||                                                                 \
                header->e_shoff + (header->e_shnum * sizeof(sec_ ## base)) > info->file_size) {                                                         \
                    return ft_printf_fd(2, "Section table goes past the end of file\n");                                                                \
            }                                                                                                                                           \
            if (header->e_machine == EM_NONE){                                                                                                          \
                return ft_printf_fd(2, "Architecture not handled\n");                                                                                   \
            }                                                                                                                                           \
            if (sizeof(elf_ ## base) >= info->file_size) {                                                                                              \
                return ft_printf_fd(2, "Symbol table or string table not found\n");                                                                     \
            }                                                                                                                                           \
            if (header->e_ident[EI_CLASS] != ELFCLASS64 &&                                                                                              \
                header->e_ident[EI_DATA] != ELFDATA2LSB &&                                                                                              \
                header->e_type != ET_EXEC &&                                                                                                            \
                header->e_type != ET_DYN) {                                                                                                             \
                    return ft_printf_fd(2, "Symbol table or string table not found\n");                                                                 \
            }                                                                                                                                           \
            if (header->e_shnum >= SHN_LORESERVE) return ft_printf_fd(2, "Too many sections\n");                                                        \
    
            
    if (info->arch == ARCH_32) {
        CHECK_ELF_HEADER(32);
    } else {
        CHECK_ELF_HEADER(64);
    }
    
    #undef CHECK_ELF_HEADER
            
    return 0;
}

static int check_arch(unsigned char *e_ident, file_info *info) {
    if (!e_ident) {
        write(2, "Wrongly formatted or corrupted ELF ident\n", 41);
        return 1;
    } 
    
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
        ft_printf_fd(2, "nm: \'%s\' : %s\n", file_path, strerror(errno));
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
    ret = check_elf(info);
    
    return ret;
}
