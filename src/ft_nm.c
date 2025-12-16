/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:29:31 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/16 19:52:36 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/* 
typedef struct s_file_info {
    char *file_name;
    char *elf_file;
    size_t file_size;
    Arch arch;
}   file_info;
*/

int ft_nm(file_info *info, Flags flags) {
    /* Total amount of symbols */
    uint32_t str_tab_index = 0;

    /* Array of symbols */
    sym_64 *symbol_array = NULL;
    int symbols_count = 0;

    elf_64 *header = (elf_64 *)info->elf_file;
    /* Checks on elf header's values */
    
    sec_64 *sec_headers = (sec_64 *)(info->elf_file + header->e_shoff);
    
    
}