/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:36:16 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/12 14:50:32 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/*  distinguish between 32 and 64 bits! */
char set_flag(uint8_t info, uint16_t shndx, char *sec_name) {
    
    uint8_t binding = ELF64_ST_BIND(info);
    uint8_t type = ELF64_ST_TYPE(info);

    printf("binding: %d | type: %d | sec_name: %s", binding, type, sec_name);

    /* Symbol is undefined */
    if (shndx == SHN_UNDEF && binding != STB_WEAK) return 'U';
    
    if (binding == STB_WEAK) {
        if (shndx == SHN_UNDEF) {
            return 'w';
        } else {
            return 'W';
        }
    }
    
    if (shndx == SHN_COMMON) {
        if (binding == STB_GLOBAL) {
            return 'c';
        }
        return 'C';
    }

    /* Symbol is defined */
    if (sec_name != NULL) {
        if (ft_strncmp(sec_name, ".text", 5) == 0) {
            if (binding == STB_GLOBAL) {
                return 'T';
            }
            return 't';
        };
        if (ft_strncmp(sec_name, ".rodata", 7) == 0) {
            if (binding == STB_GLOBAL) {
                return 'R';
            }
            return 'r';
        };
        if (ft_strncmp(sec_name, ".data", 5) == 0) {
            if (binding == STB_GLOBAL) {
                return 'D';
            }
            return 'd';
        };
        if (ft_strncmp(sec_name, ".bss", 4) == 0) {
            if (binding == STB_GLOBAL) {
                return 'B';
            }
            return 'b';
        };
    }

    return '?';
}