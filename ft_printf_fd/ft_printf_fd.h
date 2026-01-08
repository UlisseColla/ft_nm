/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:35:13 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/21 18:26:13 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>

int	ft_printf_fd(int fd, const char *str, ...);
int	ft_strlength(char *s);
int	ft_putstr(char *s, int fd);
int	ft_putnbr(long n, int fd);
int	ft_putnbr_base(unsigned int nbr, char *base, int fd);
int	ft_putptr(uintptr_t ptr, char *base, int fd);
int	ft_put_unsigned(unsigned int n, int fd);
int	ft_count_digits(int n);

static inline int ft_putchar(char c, int fd) {
    write(fd, &c, 1);
	return 1;
}

#endif