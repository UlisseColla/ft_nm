/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:25:09 by ucolla            #+#    #+#             */
/*   Updated: 2023/10/19 11:25:29 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)malloc(ft_strlen(s) + 1 * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*char	fd_toupper(unsigned int a, char c)
{
	a = 0;
	if (c >= 'a' && c <= 'z')
		return (c - 32) + a;
	else
		return (c) + a;
}

int main()
{
	char *str = "LoReM iPsUm";
	char *str2 = ft_strmapi(str, &fd_toupper);
	printf("%s\n", str2);
	return (0);
}*/