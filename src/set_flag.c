/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:36:16 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/11 17:45:18 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/*  distinguish between 34 and 64 bits! */
char set_flag(uint8_t info, uint16_t shndx, char *sec_name) {
    
    uint8_t binding = ELF64_ST_BIND(info);

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
        if (ft_strncmp(sec_name, ".text", 5)) {
            if (binding == STB_GLOBAL) {
                return 't';
            }
            return 'T';
        };
        if (ft_strncmp(sec_name, ".rodata", 7)) {
            if (binding == STB_GLOBAL) {
                return 'r';
            }
            return 'R';
        };
        if (ft_strncmp(sec_name, ".data", 5)) {
            if (binding == STB_GLOBAL) {
                return 'd';
            }
            return 'D';
        };
        if (ft_strncmp(sec_name, ".bss", 4)) {
            if (binding == STB_GLOBAL) {
                return 'b';
            }
            return 'B';
        };
    }

    return '?';
}