/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:07:11 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/05 19:09:06 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
#define FT_NM_H

#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <elf.h>
#include "libft.h"

typedef Elf64_Ehdr elf_h;
typedef Elf64_Shdr sec_h;

#define ARGUMENTS_ERROR "Wrong number of arguments\n"

#define WRITE(string) \
            int n = ft_strlen(string); \
            write(1, string, n);

void print_ekh_header(elf_h *ekh);
void print_sec_header(sec_h *header);          

#endif
