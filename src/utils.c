/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:47:25 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/05 19:12:05 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void print_ekh_header(elf_h *ekh) {
    printf("Header size: %d\n", ekh->e_ehsize);
    /* printf("E_ident |");
    for(int i = 0; i < (int)sizeof(ekh->e_ident); i++) {
        printf("%x ", ekh[i]);
    }
    printf("|\n"); */

    printf("Type: %d\n", ekh->e_type);
    printf("Machine: %d\n", ekh->e_machine);
    printf("Version: %d\n", ekh->e_version);
    printf("Ph_off: %ld\n", ekh->e_phoff);
    printf("Sh_off: %ld\n", ekh->e_shoff);
    printf("Flags: %d\n", ekh->e_flags);
    printf("Phentsize: %d\n", ekh->e_phentsize);
    printf("Phnum: %d\n", ekh->e_phnum);
    printf("Shentsize: %d\n", ekh->e_shentsize);
    printf("Shnum: %d\n", ekh->e_shnum);
    printf("Shstrndx: %d\n", ekh->e_shstrndx);
}

void print_sec_header(sec_h *header) {
    printf("Section size: %ld\n", header->sh_size);
    printf("Type: %d\n", header->sh_type);
    printf("Flags: %ld\n", header->sh_flags);
    printf("Addr: %ld\n", header->sh_addr);
    printf("Name: %d\n", header->sh_name);
    printf("Sh_off: %ld\n", header->sh_offset);
    printf("Info: %d\n", header->sh_info);
    printf("Link: %d\n", header->sh_link);
    printf("Addraling: %ld\n", header->sh_addralign);
    printf("Entsize: %ld\n", header->sh_entsize);
}
