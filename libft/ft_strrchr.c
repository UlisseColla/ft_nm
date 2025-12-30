/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:27:55 by ucolla            #+#    #+#             */
/*   Updated: 2023/10/10 15:35:40 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	a;
	char			*str;

	i = ft_strlen(s);
	a = c;
	str = (char *)s;
	while (i >= 0)
	{
		if (str[i] == a)
			return (&str[i]);
		i--;
	}
	return (NULL);
}
