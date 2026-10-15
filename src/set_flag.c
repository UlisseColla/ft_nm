/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:36:16 by ucolla            #+#    #+#             */
/*   Updated: 2026/10/15 18:18:38 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/* Core logic, independent of ELF class.
 * sec_valid == 0 means no real section is associated (reserved shndx
 * or out-of-bounds index), so sh_type / sh_flags must be ignored. */
static char classify(uint8_t type, uint8_t bind, uint16_t shndx,
                     int sec_valid, uint64_t sh_type, uint64_t sh_flags)
{
    int local = (bind == STB_LOCAL);

    /* 1. Special section indexes */
    if (shndx == SHN_UNDEF) {
        if (bind == STB_WEAK)
            return type == STT_OBJECT ? 'v' : 'w';
        return 'U';
    }
    if (shndx == SHN_ABS)
        return local ? 'a' : 'A';
    if (shndx == SHN_COMMON)
        return 'C';

    if (bind == STB_GNU_UNIQUE)
        return 'u';
    if (type == STT_GNU_IFUNC)
        return 'i';

    /* Any other index must point to a real, in-bounds section */
    if (!sec_valid)
        return '?';

    /* 3. Weak, defined */
    if (bind == STB_WEAK)
        return type == STT_OBJECT ? 'V' : 'W';

    /* 4. Section flags decide the letter */
    if (sh_flags & SHF_EXECINSTR)
        return local ? 't' : 'T';
    if (!(sh_flags & SHF_ALLOC))
        return '?';
    if (sh_type == SHT_NOBITS)
        return local ? 'b' : 'B';
    if (!(sh_flags & SHF_WRITE))
        return local ? 'r' : 'R';
    return local ? 'd' : 'D';
}

char set_flag(void *sym, void *sections, void *max, Arch arch)
{
    uint8_t  type, bind;
    uint16_t shndx;
    int      sec_valid = 0;
    uint64_t sh_type = 0, sh_flags = 0;

    if (arch == ARCH_32) {
        sym_32 *s = (sym_32 *)sym;

        type  = ELF32_ST_TYPE(s->st_info);
        bind  = ELF32_ST_BIND(s->st_info);
        shndx = s->st_shndx;
        if (shndx != SHN_UNDEF && shndx < SHN_LORESERVE) {
            sec_32 *sec = &((sec_32 *)sections)[shndx];
            if ((void *)(sec + 1) <= max) {
                sec_valid = 1;
                sh_type   = sec->sh_type;
                sh_flags  = sec->sh_flags;
            }
        }
    } else {
        sym_64 *s = (sym_64 *)sym;

        type  = ELF64_ST_TYPE(s->st_info);
        bind  = ELF64_ST_BIND(s->st_info);
        shndx = s->st_shndx;
        if (shndx != SHN_UNDEF && shndx < SHN_LORESERVE) {
            sec_64 *sec = &((sec_64 *)sections)[shndx];
            if ((void *)(sec + 1) <= max) {
                sec_valid = 1;
                sh_type   = sec->sh_type;
                sh_flags  = sec->sh_flags;
            }
        }
    }
    return classify(type, bind, shndx, sec_valid, sh_type, sh_flags);
}

// 2. Handle File Symbols ('f')
/* if (type == STT_FILE) {
    return 'f';
} */
