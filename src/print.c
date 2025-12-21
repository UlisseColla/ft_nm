/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:18:32 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/21 16:40:23 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void debug_prints(t_list *files, Flags flags) {
    while(files->next) {
        printf("File is: %s\n", (char *)files->content);
        files = files->next;
    }
    printf("File is: %s\n\n", (char *)files->content);
    printf("Flag are - sort: %d - filter: %d\n", flags.sort, flags.filter);
}

void print_ekh_header(elf_64 *ekh) {
    printf("ELF HEADER\n");
    printf("Header size: %d\n", ekh->e_ehsize);

    // 1. Types & Machine (Keep Hex, strictly 2 bytes -> 4 hex chars)
    printf("Type:      0x%04x\n", ekh->e_type);
    printf("Machine:   0x%04x\n", ekh->e_machine);

    // 2. Version (Keep Hex, 4 bytes -> 8 hex chars)
    printf("Version:   0x%08x\n", ekh->e_version);

    // 3. Offsets (Use Long Hex for 64-bit addresses)
    printf("Ph_off:    0x%lx\n",  ekh->e_phoff);
    printf("Sh_off:    0x%lx\n",  ekh->e_shoff);

    // 4. Flags (Hex is standard for bitmasks)
    printf("Flags:     0x%08x\n", ekh->e_flags);

    // 5. Header Sizes (Decimal is easier to read for sizes)
    printf("Ehsize:    %d (bytes)\n", ekh->e_ehsize);
    printf("Phentsize: %d (bytes)\n", ekh->e_phentsize);
    printf("Shentsize: %d (bytes)\n", ekh->e_shentsize);

    // 6. Counts (Decimal is easier to read for quantities)
    printf("Phnum:     %d\n", ekh->e_phnum);
    printf("Shnum:     %d\n", ekh->e_shnum);
    printf("Shstrndx:  %d\n\n", ekh->e_shstrndx);
}

void print_sec_64eader(sec_64 *header) {
    printf("Section size:   %ld (bytes)\n", header->sh_size);
    printf("Type:           0x%04x\n", header->sh_type);
    printf("Flags:          0x%lx\n", header->sh_flags);
    printf("Addr:           0x%lx\n", header->sh_addr);
    printf("Name:           0x%x\n", header->sh_name);
    printf("Sh_off:         %ld\n", header->sh_offset);
    printf("Info:           %d\n", header->sh_info);
    printf("Link:           %d\n", header->sh_link);
    printf("Addraling:      0x%lx\n", header->sh_addralign);
    printf("Entsize:        %ld (bytes)\n\n", header->sh_entsize);
}

void print_line(symbol s) {
    if (s.name == NULL) return;
    if (s.address != NULL) {
        for (int i = 0; i < (16 - (int)ft_strlen(s.address)); i++) {
            write(1, "0", 1);
        }
        ft_printf_fd(1, "%s", s.address);
    } else {
        for(int i = 0; i < 16; i++) {
            write(1, " ", 1);
        }
    }
    ft_printf_fd(1, " %c ", s.type);
    ft_printf_fd(1, "%s\n", s.name);
}

void print_symbols(int size, symbol *array, Flags flags) {
    switch(flags.filter) {
        case UNDEFINED:
            for(int i = 0; i < size; i++) {
                if (array[i].type == 'U') print_line(array[i]);
            };
            break;
        case EXTERNAL:
            /* to be finished */
            break;
        case ALL:
            /* to be finished */
            break;
        default:
            for(int i = 0; i < size; i++) {
                print_line(array[i]);
            };
            break;
    }
}

void print_symbols_r(int size, symbol *array, Flags flags) {
    switch(flags.filter) {
        case UNDEFINED:
            for(int i = size - 1; i >= 0; i--) {
                if (array[i].type == 'U') print_line(array[i]);
            };
            break;
        case EXTERNAL:
            /* to be finished */
            break;
        case ALL:
            /* to be finished */
            break;
        default:
            for(int i = size - 1; i >= 0; i--) {
                print_line(array[i]);
            };
            break;
    }
}
