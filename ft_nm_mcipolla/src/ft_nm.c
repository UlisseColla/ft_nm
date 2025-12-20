# include <ft_nm.h>
#include <string.h>

char get_section_type(unsigned char binding, uint16_t shndx, section_props_t *sec_props, uint16_t n_sections)
{
    char modifier = (binding == STB_LOCAL) ? ('a' - 'A') : 0;

    if (shndx >= n_sections) return '?';

    if (sec_props[shndx].is_bss) return 'B' + modifier;
    else if (sec_props[shndx].is_text) return 'T' + modifier;
    else if (sec_props[shndx].is_rodata) return 'R' + modifier;
    else if (sec_props[shndx].is_data) return 'D' + modifier;
    else return 'N';
}

char get_type(unsigned char type, unsigned char binding, uint16_t st_shndx, int8_t is_rodata, int8_t is_bss, int8_t is_data)
{
    char modifier = (binding == STB_LOCAL) ? ('a' - 'A') : 0;

    if (st_shndx == SHN_UNDEF) return (binding == STB_WEAK ? 'w' : 'U');
    else if (st_shndx == SHN_COMMON){
        if (binding == STB_WEAK) {
            if (type == STT_FUNC) return 'W';
            else return 'V';
        } else return 'C';
    }
    else if (st_shndx == SHN_ABS) return 'a';
    else if (binding == STB_WEAK) {
        if(type == STT_OBJECT)
          return(st_shndx == SHN_UNDEF) ? 'v' : 'V';
        else
          return(st_shndx == SHN_UNDEF) ? 'w' : 'W';
    }
    else if (type == STT_FUNC) return 'T' + modifier;
    else if (is_bss) return 'B' + modifier;
    else if (is_rodata) return 'R' + modifier;
    else if (is_data) return 'D' + modifier; 
    else if (type == STT_OBJECT) return 'D' + modifier;
    else if (type == STT_NOTYPE) return 'N' + modifier;
    return '?'; 
}


void print_entries(symbols_t *entries, int n_symbols, elf_type type, char *filename)
{
    static int printed_file = 0;

    if (n_files > 1) {
        ft_fprintf(1, "\n%s:\n", filename);
        printed_file++;
    }
    if (!flags.p) quick_sort(entries, 0, n_symbols - 1);
    if (flags.r) {
        for (int i = n_symbols - 1; i > 0; i--) {
            if (!ft_strlen(entries[i].name) && entries[i].type != 'a') continue; 
            if ((entries[i].type == 'a' || entries[i].type == 'N' || entries[i].type == 'n') && !flags.a) continue;
            if ((entries[i].type == 't' || entries[i].type == 'r' ||
                entries[i].type == 'b' || entries[i].type == 'd') && flags.g) continue;
                if (flags.u && (entries[i].type != 'w' && entries[i].type != 'U')) continue;
            int j = i;
            while (j > 0 && !ft_strcmp(entries[j].name, entries[j - 1].name)) {
                j--;
            }
            int diff = i - j;
            while (j <= i) {
                if (((entries[j].value == 0 && entries[j].type == 'W') ||
                    (entries[j].value == 0 && entries[j].type == 'w') ||
                    entries[j].type == 'U'))
                    ft_fprintf(1, (type == ELF32) ? "         " : "                 ");
                else
                    ft_fprintf(1, (type == ELF32) ? "%08x " : "%016x ", entries[j].value);
                ft_fprintf(1, "%c %s\n", entries[j].type, entries[j].name);
                j++;
            }
            i -= diff;
        }
    } else {
        for (int i = 0; i < n_symbols; i++) {
            if (!ft_strlen(entries[i].name) && entries[i].type != 'a') continue; 
            if ((entries[i].type == 'a' || entries[i].type == 'N' || entries[i].type == 'n') && !flags.a) continue;
            if ((entries[i].type == 't' || entries[i].type == 'r' ||
                entries[i].type == 'b' || entries[i].type == 'd') && flags.g) continue;
                if (flags.u && (entries[i].type != 'w' && entries[i].type != 'U')) continue;
            if (((entries[i].value == 0 && entries[i].type == 'W') ||
                (entries[i].value == 0 && entries[i].type == 'w') ||
                entries[i].type == 'U'))
                ft_fprintf(1, (type == ELF32) ? "         " : "                 ");
            else
                ft_fprintf(1, (type == ELF32) ? "%08x " : "%016x ", entries[i].value);
            ft_fprintf(1, "%c %s\n", entries[i].type, entries[i].name);
        }
    }
}

static int extract_symbols(void *symtab, void *strtab, void *shdr, void *shstrtab_ptr, 
                           int n_symbols, uint16_t n_sections, elf_type type, 
                           section_props_t *sec_props, symbols_t *entries, int *idx) {
    #define GET_ENTRIES(base)   \
            Elf ## base ##_Sym *cast_sym = (Elf ## base ##_Sym *)symtab;    \
            Elf ## base ##_Shdr *cast_shdr = (Elf ## base ##_Shdr *)shdr;   \
            uint16_t shndx = cast_sym[i].st_shndx;                          \
            unsigned char binding = type == ELF64 ? ELF64_ST_BIND(cast_sym[i].st_info) : ELF32_ST_BIND(cast_sym[i].st_info); \
            unsigned char sym_type = type == ELF64 ? ELF64_ST_TYPE(cast_sym[i].st_info) : ELF32_ST_TYPE(cast_sym[i].st_info); \
                                                                            \
            entries[*idx].value = cast_sym[i].st_value;                     \
                                                                            \
            if (cast_sym[i].st_name == 0 && shndx < n_sections && shndx != SHN_UNDEF && flags.a) { \
                entries[*idx].name = ((char *)shstrtab_ptr + cast_shdr[shndx].sh_name); \
                entries[*idx].type = get_section_type(binding, shndx, sec_props, n_sections); \
                if (!ft_strcmp(entries[*idx].name, ".comment")) entries[*idx].type = 'n'; \
            } else {                                                          \
                entries[*idx].name = ((char *)strtab + cast_sym[i].st_name);  \
                if (shndx < n_sections && sec_props) {                                   \
                    entries[*idx].type = get_type(sym_type, binding, shndx, sec_props[shndx].is_rodata, sec_props[shndx].is_bss, sec_props[shndx].is_data); \
                } else {                                                    \
                    entries[*idx].type = get_type(sym_type, binding, shndx, 0, 0, 0); \
                }                                                           \
            }

    for (int i = 0; i < n_symbols; i++) {
        switch (type) {
            case ELF64: {GET_ENTRIES(64); break;}
            case ELF32: {GET_ENTRIES(32); break;}
        }

        (*idx)++;
    }
    #undef GET_ENTRIES
    return 0;
}

int ft_nm(void *map, struct stat st, char *filename)
{
    unsigned char *e_indent = (unsigned char *)map;
    if (e_indent[0] != ELFMAG0 || e_indent[1] != ELFMAG1 ||
        e_indent[2] != ELFMAG2 || e_indent[3] != ELFMAG3) {
            return 1;
        }
    if (e_indent[EI_VERSION] != 1) return ft_fprintf(2, "ft_nm: %s: file format not recognized\n", filename);
    const char endianess = e_indent[EI_DATA];
    if(endianess != 1 && endianess != 2) return ft_fprintf(1, "bfd plugin: LLVM gold plugin has failed to create LTO module: Invalid ELF data\n");
    flags.endianess = endianess;
    void *symtab = NULL, *strtab = NULL, *shdr = NULL, *shstrtab_ptr = NULL;
    uint32_t n_symbols = 0;
    elf_type type;
    section_props_t *sec_props = NULL;
    uint16_t n_sections;
    
    #define READ_ELF_HEADER(base) \
            type = ELF ## base;                                 \
            size_t ehsize_std = base == 64 ? 64 : 52;   \
            Elf ## base ##_Ehdr *ehdr = (Elf ## base ##_Ehdr *)map;   \
            if (ehdr->e_shoff > (long unsigned)st.st_size) {    \
                return ft_fprintf(1, "bfd plugin: LLVM gold plugin has failed to create LTO module: section header table goes past the end of the file: e_shoff = 0x%s\n", ft_itoa(ehdr->e_shoff, 16));   \
            }; \
            if (ehdr->e_ehsize < ehsize_std || ehdr->e_ehsize > 256) return ft_fprintf(2,"ft_nm: %s: file format not recognized\n", filename); \
            if (ehdr->e_shentsize != sizeof(Elf ## base ##_Shdr)) \
            return ft_fprintf(1, "bfd plugin: LLVM gold plugin has failed to create LTO module: invalid e_shentsize in ELF header: %s\n", ft_itoa(ehdr->e_shentsize, 10)); \
            if (!ehdr->e_shnum || !ehdr->e_shoff || ehdr->e_version == EV_NONE ||   \
                (long unsigned)st.st_size < ehdr->e_shoff + (sizeof(Elf ## base ##_Shdr) * ehdr->e_shnum)) {    \
                    return ft_fprintf(1, "bfd plugin: LLVM gold plugin has failed to create LTO module: section table goes past the end of file\n"); \
            }   \
            if (check_ehdr(map, st, type)) return 1;    \
            Elf ## base ##_Shdr *elf_shdr = map + ehdr->e_shoff;   \
            shstrtab_ptr = (char *)map + elf_shdr[ehdr->e_shstrndx].sh_offset;  \
            shdr = elf_shdr;    \
            if (elf_shdr[0].sh_size != 0 && elf_shdr[0].sh_offset != 0) {    \
                return ft_fprintf(2, "error: bad shdr\n");    \
            }   \
            if (ehdr->e_shstrndx >= ehdr->e_shnum ||    \
                elf_shdr[ehdr->e_shstrndx].sh_type != SHT_STRTAB) { \
                return ft_fprintf(1, "bfd plugin: %s: ELF section name out of range\n", filename);  \
            }   \
            shstrtab_ptr = (char *)map + elf_shdr[ehdr->e_shstrndx].sh_offset; \
            shdr = elf_shdr;    \
            n_sections = ehdr->e_shnum; \
            if (n_sections == 0) {  \
                return ft_fprintf(2, "ft_nm: %s: file format not recognized\n", filename);  \
            }   \
            sec_props = malloc(n_sections * sizeof(section_props_t));   \
            for (int i = 0; i < n_sections; i++) sec_props[i] = (section_props_t){}; \
            for (uint16_t i = 0; i < n_sections; i++) { \
                if (elf_shdr[i].sh_name > elf_shdr[ehdr->e_shstrndx].sh_size) { \
                    ft_fprintf(2, "ELF section name out of range\n");  \
                    free(sec_props);    \
                    return ehdr->e_type == ET_DYN ? 1 : ehdr->e_type == ET_REL ? 0 : 1; \
                }   \
                if (elf_shdr[i].sh_type == SHT_NOBITS && (elf_shdr[i].sh_flags & SHF_ALLOC)) {  \
                    sec_props[i].is_bss = 1;    \
                } else if ((elf_shdr[i].sh_flags & SHF_ALLOC) && (elf_shdr[i].sh_flags & SHF_EXECINSTR) && (elf_shdr[i].sh_type == SHT_PROGBITS)) {   \
                    sec_props[i].is_text = 1;   \
                } else if ((elf_shdr[i].sh_flags & SHF_ALLOC) && !(elf_shdr[i].sh_flags & SHF_WRITE)) { \
                    sec_props[i].is_rodata = 1; \
                } else if ((elf_shdr[i].sh_flags & SHF_ALLOC) && (elf_shdr[i].sh_flags & SHF_WRITE) && (elf_shdr[i].sh_type != SHT_NOBITS)) {   \
                    sec_props[i].is_data = 1;   \
                } \
                if (elf_shdr[i].sh_type == SHT_SYMTAB) {    \
                    symtab = (char *)map + elf_shdr[i].sh_offset;   \
                    n_symbols = elf_shdr[i].sh_size / elf_shdr[i].sh_entsize;   \
                    strtab = (char *)map + elf_shdr[elf_shdr[i].sh_link].sh_offset; \
                }   \
            }   
    // end define
    if (e_indent[EI_CLASS] == ELFCLASS64) { READ_ELF_HEADER(64); }
    else if (e_indent[EI_CLASS] == ELFCLASS32) { READ_ELF_HEADER(32); }
    else {
        return ft_fprintf(1, "bfd plugin: LLVM gold plugin has failed to create LTO module: Invalid ELF class\n");
    }

    if (symtab && strtab && shdr) {
        symbols_t *entries = malloc(sizeof(symbols_t) * (n_symbols));
        int entries_idx = 0;
        extract_symbols(symtab, strtab, shdr, shstrtab_ptr, n_symbols, n_sections, type, sec_props, entries, &entries_idx);
        print_entries(entries, entries_idx, type, filename);
        free(sec_props);
        free(entries);
        return 0;
    }
    free(sec_props);
    ft_fprintf(2, "ft_nm: %s: file format not recognized\n", filename);
    return 1;
}
