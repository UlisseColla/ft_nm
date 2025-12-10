/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_address.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:45:06 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/10 18:13:57 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char *get_address(uint64_t addr) {
    uint8_t buf[16];
    char ret[16];
    char base[] = "0123456789abcdef";
    int l = 0;
    int i = 0; 
    
    while(addr) {
        buf[i] = addr % 16;
        addr /= 16;
        i++;
    }
    
    i--;
    while(i >= 0) {
        ret[l] = base[buf[i]];
        l++;
        i--;
    }
    ret[l] = '\0';
    
    return ft_strdup(ret);
}
