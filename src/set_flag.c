/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:36:16 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/15 18:52:31 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/*  distinguish between 32 and 64 bits! */
char set_flag(sym_h *sym, sec_h *sections, void *max) {
    uint8_t type = ELF64_ST_TYPE(sym->st_info);
    uint8_t bind = ELF64_ST_BIND(sym->st_info);
    uint64_t shndx = sym->st_shndx;

    sec_h *sym_sec = &(sections[shndx]);
    if ((void *)sym_sec > max) return 'a';
    uint64_t readonly = !(sym_sec->sh_flags & SHF_WRITE);

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

    if (shndx == SHN_ABS)
		return 'a';

    if (bind == STB_WEAK) {
		if (type == STT_OBJECT)
			return sym->st_value <= 0 ? 'v' : 'V';
		return sym->st_value <= 0 ? 'w' : 'W';
	}

    if (sym_sec->sh_type == SHT_NOBITS) {
		return bind == STB_LOCAL ? 'b' : 'B';
	}

	if (shndx == SHN_UNDEF)
		return 'U';
    
    if (type == STT_NOTYPE || type == STT_OBJECT) {
		if (readonly)
			return bind == STB_LOCAL ? 'r' : 'R';
		return bind == STB_LOCAL ? 'd' : 'D';
	}

    switch (type) {
		case STT_COMMON:
			return bind == STB_LOCAL ? 'c' : 'C';
		case STT_FUNC:
			return bind == STB_LOCAL ? 't' : 'T';
		default:
			break;
	}

    return '?';
}