/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:36:16 by ucolla            #+#    #+#             */
/*   Updated: 2026/02/15 16:07:53 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

// 2. Handle File Symbols ('f')
/* if (type == STT_FILE) {
    return 'f';
} */
char set_flag(void *sym, void *sections, void *max, Arch arch) {

    #define SET_FLAG(base)                                                      \
            uint8_t type = ELF64_ST_TYPE(((sym_ ## base *)sym)->st_info);       \
            uint8_t bind = ELF64_ST_BIND(((sym_ ## base *)sym)->st_info);       \
            uint64_t shndx = ((sym_ ## base *)sym)->st_shndx;                   \
            uint64_t value = ((sym_ ## base *)sym)->st_value;                   \
            sec_ ## base *sym_sec = &(((sec_ ## base *)sections)[shndx]);       \
            if ((void *)sym_sec > max) return 'a';                              \
            uint64_t readonly = !(sym_sec->sh_flags & SHF_WRITE);               \
            if (shndx == SHN_ABS) {                                             \
                return (bind == STB_LOCAL) ? 'a' : 'A';                         \
            }                                                                   \
            if (bind == STB_WEAK) {                                             \
                if (type == STT_OBJECT)                                         \
                    return value <= 0 ? 'v' : 'V';                              \
                return value <= 0 ? 'w' : 'W';                                  \
            }                                                                   \
            if (sym_sec->sh_type == SHT_NOBITS) {                               \
                return bind == STB_LOCAL ? 'b' : 'B';                           \
            }                                                                   \
            if (shndx == SHN_UNDEF) return 'U';                                 \
            if (type == STT_NOTYPE || type == STT_OBJECT) {                     \
                if (readonly)                                                   \
                    return bind == STB_LOCAL ? 'r' : 'R';                       \
                return bind == STB_LOCAL ? 'd' : 'D';                           \
            }                                                                   \
            switch (type) {                                                     \
                case STT_COMMON:                                                \
                    return bind == STB_LOCAL ? 'c' : 'C';                       \
                case STT_FUNC:                                                  \
                    return bind == STB_LOCAL ? 't' : 'T';                       \
                default:                                                        \
                    break;                                                      \
            }                                                                   \
            return '?';                                                         \

    if (arch == ARCH_32) {
        SET_FLAG(32);
    } else {
        SET_FLAG(64);
    }
            
    #undef SET_FLAG
}

/* Symbol is undefined */
    /* if (shndx == SHN_UNDEF && binding != STB_WEAK) return 'U';
    
    if (binding == STB_WEAK) {
        if (shndx == SHN_UNDEF) {
            return 'w';
        } else {
            return 'W';
        }
    }
    
    if (shndx == SHN_COMMON) return binding == STB_GLOBAL ? 'C' : 'c'; */

    /* if (ft_strncmp(sec_name, ".text", 5) == 0 ||
        ft_strncmp(sec_name, ".init", 5) == 0 ||
        ft_strncmp(sec_name, ".fini", 5) == 0
    ) {
        return binding == STB_GLOBAL ? 'T' : 't';
    };
    if (ft_strncmp(sec_name, ".rodata", 7) == 0) {
        return binding == STB_GLOBAL ? 'R' : 'r';
    };
    if (ft_strncmp(sec_name, ".data", 5) == 0) {
        return binding == STB_GLOBAL ? 'D' : 'd';
    };
    if (ft_strncmp(sec_name, ".bss", 4) == 0) {
        return binding == STB_GLOBAL ? 'B' : 'b';
    }; */