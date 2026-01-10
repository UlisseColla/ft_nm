/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:13:06 by ucolla            #+#    #+#             */
/*   Updated: 2023/10/19 14:20:53 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!dst || !src || size == 0)
		return (ft_strlen(src));
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

/*int main()
{
	char dest[20];
	char src[] = "";
	//ft_strlcpy(dest, src, 0);
	printf("src: %s || dest: %s || strlen di src: %ld\n", 
	src, dest, ft_strlcpy(dest, "", 15));
	write(1, "\n", 1);
    write(1, dest, 15);

}*/