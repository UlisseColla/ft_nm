#include <ft_nm.h>
#include <stdarg.h>



int check_ehdr(void *map, struct stat st, elf_type type)
{
    #define CHECK_HEADER(i) \
    Elf ## i ##_Ehdr *ehdr = (Elf ## i ##_Ehdr *)map;                           \
    if (ehdr->e_machine == EM_NONE)                                             \
    return ft_fprintf(1,"Architecture not handled\n");                          \
    if ((long unsigned)st.st_size <= sizeof(Elf ## i ##_Ehdr))                  \
    return ft_fprintf(1, "Symbol table or string table not found\n");           \
    if (ehdr->e_ident[EI_CLASS] != ELFCLASS64 &&                                \
        ehdr->e_ident[EI_DATA] != ELFDATA2LSB) {                                \
        if (ehdr->e_type != ET_EXEC && ehdr->e_type != ET_DYN)                  \
            return ft_fprintf(1, "Symbol table or string table not found\n");   \
    }                                                                           \
    if (ehdr->e_shnum >= SHN_LORESERVE)                                         \
    return ft_fprintf(1, "Too many sections\n");

    if (type == ELF64) {
        CHECK_HEADER(64);
    } else {
        CHECK_HEADER(32);
    }
    return 0;
    
    #undef CHECK_HEADER
}

size_t ft_strlen(const char *s)
{
    char *p = (char *)s;
    while (*p) p++;
    return p - s;
}

char result[64];
char* ft_itoa(int value, int base)
{
    char tmp_char;
    int tmp_value;
    char *ptr = result, *ptr1 = result;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
  
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

static char ft_to_lower(char c)
{
    if (c >= 'A' && c <= 'Z') {
        return (c + 32);
    }
    return c;
}

int ft_nm_strcmp(char *s1, char *s2)
{
    int i = 0;
    int j = 0;
    char *cp1 = (char *)s1;
    char *cp2 = (char *)s2;
    
    while (cp1[i] && cp2[j]) {
        while (cp1[i] && (cp1[i] == '_' || cp1[i] == '@' || cp1[i] == '.')) i++;
        while (cp2[j] && (cp2[j] == '_' || cp2[j] == '@' || cp2[j] == '.')) j++;
        if (ft_to_lower(cp1[i]) != ft_to_lower(cp2[j])) {
            break;
        }
        j++;
        i++;
    }
    return ft_to_lower(cp1[i]) - ft_to_lower(cp2[j]);
}