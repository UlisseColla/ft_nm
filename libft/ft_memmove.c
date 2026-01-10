/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:56:45 by ucolla            #+#    #+#             */
/*   Updated: 2023/10/16 19:40:08 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t						i;
	const unsigned char			*src_str;
	unsigned char				*dest_str;

	i = 0;
	src_str = (const unsigned char *)src;
	dest_str = (unsigned char *)dest;
	if (n == 0 || dest == src)
		return (dest);
	if (src_str < dest_str)
	{
		while (n--)
			dest_str[n] = src_str[n];
	}
	else
	{
		while (i < n)
		{
			dest_str[i] = src_str[i];
			i++;
		}
	}
	return (dest);
}
