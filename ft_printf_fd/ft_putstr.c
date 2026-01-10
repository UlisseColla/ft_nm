/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:03:56 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/21 18:17:13 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

int	ft_putstr(char *s, int fd)
{
	int	len;

	if (!s)
		return (ft_putstr("(null)", fd));
	len = ft_strlength(s);
	write(fd, s, len);
	return (len);
}
