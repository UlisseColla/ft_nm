/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:52:05 by ucolla            #+#    #+#             */
/*   Updated: 2023/10/19 12:23:41 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

/*char	fd_toupper(unsigned int a, char c)
{
	a = 0;
	if (c >= 'a' && c <= 'z')
		return (c - 32) + a;
	else if (c >= 'A' && c <= 'Z')
		return (c + 32) + a;
	else
		return (c) + a;
}

int main()
{
	char *str = "0123456789";
	char *str2 = ft_strmapi(str, &fd_toupper);
	printf("%s\n", str2);
	return (0);
}*/