#ifndef FT_NM_H
#define FT_NM_H

#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// uint32_t magic = ((uint32_t)ELFMAG3 << 24) | ((uint32_t) ELFMAG2 << 16) | ((uint32_t)ELFMAG1 << 8) | ((uint32_t)ELFMAG0);

/*
 * #define EI_NIDENT 16

 * typedef struct {
 *     unsigned char e_ident[EI_NIDENT];
 *     uint16_t      e_type;
 *     uint16_t      e_machine;
 *     uint32_t      e_version;
 *     ElfN_Addr     e_entry;
 *     ElfN_Off      e_phoff;
 *     ElfN_Off      e_shoff;
 *     uint32_t      e_flags;
 *     uint16_t      e_ehsize;
 *     uint16_t      e_phentsize;
 *     uint16_t      e_phnum;
 *     uint16_t      e_shentsize;
 *     uint16_t      e_shnum;
 *     uint16_t      e_shstrndx;
 * } ElfN_Ehdr;
 *
 *
 * typedef struct {                            typedef struct {
 *     uint32_t   sh_name;                         uint32_t   sh_name;
 *     uint32_t   sh_type;                         uint32_t   sh_type;
 *     uint32_t   sh_flags;                        uint64_t   sh_flags;
 *     Elf32_Addr sh_addr;                         Elf64_Addr sh_addr;
 *     Elf32_Off  sh_offset;                       Elf64_Off  sh_offset;
 *     uint32_t   sh_size;                         uint64_t   sh_size;
 *     uint32_t   sh_link;                         uint32_t   sh_link;
 *     uint32_t   sh_info;                         uint32_t   sh_info;
 *     uint32_t   sh_addralign;                    uint64_t   sh_addralign;
 *     uint32_t   sh_entsize;                      uint64_t   sh_entsize;
 * } Elf32_Shdr;                                } Elf64_Shdr;
 *
 * typedef struct {                         typedef struct {
 *     uint32_t      st_name;                   uint32_t      st_name;
 *     Elf32_Addr    st_value;                  unsigned char st_info;
 *     uint32_t      st_size;                   unsigned char st_other;
 *     unsigned char st_info;                   uint16_t      st_shndx;
 *     unsigned char st_other;                  Elf64_Addr    st_value;
 *     uint16_t      st_shndx;                  uint64_t      st_size;
 * } Elf32_Sym;                             } Elf64_Sym;
 *
*/

typedef struct {
    long unsigned int value;
    char type;
    char *name;
} symbols_t;

typedef enum { ELF32, ELF64 } elf_type;

typedef struct {
    int8_t is_bss;
    int8_t is_rodata;
    int8_t is_data;
    int8_t is_text;
} section_props_t;

typedef struct {
    void            *ehdr;
    void            *shdr;
    void            *symtab;
    void            *strtab;
    int             n_symbols;
    int             n_sections;
    elf_type        type;
    section_props_t *props;
}   elf_data_t;

typedef struct {
    uint8_t a         : 1;
    uint8_t g         : 1;
    uint8_t u         : 1;
    uint8_t r         : 1;
    uint8_t p         : 1;
    uint8_t endianess : 2;
}   flag_t;

extern flag_t flags;
extern int n_files;

int ft_nm(void *map, struct stat st, char *filename);
void quick_sort(symbols_t array[], int lower, int higher);
int check_ehdr(void *map, struct stat st, elf_type type);
size_t ft_strlen(const char *s);
char* ft_itoa(int value, int base);
int ft_fprintf(int fd, const char *fmt, ...);
int ft_strcmp(const char *s1, const char *s2);
int ft_nm_strcmp(char *s1, char *s2);

#endif
