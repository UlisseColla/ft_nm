/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:12:44 by ucolla            #+#    #+#             */
/*   Updated: 2023/10/16 17:44:17 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	a;
	size_t			i;
	char			*str;

	a = c;
	i = 0;
	str = (char *)s;
	if (!str)
		return (NULL);
	if (a == '\0')
		return (str + ft_strlen(s));
	while (str[i] != '\0')
	{
		if (str[i] == a)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
