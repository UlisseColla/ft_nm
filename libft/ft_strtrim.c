/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:49:07 by ucolla            #+#    #+#             */
/*   Updated: 2023/10/24 15:13:52 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	start(char const *s1, char const *set)
{
	size_t	i;
	size_t	k;

	i = 0;
	while (s1[i] != '\0')
	{
		k = 0;
		while (set[k] != '\0')
		{
			if (s1[i] != set[k])
				k++;
			else
				break ;
		}
		if (set[k] == '\0' && s1[i] != set[k])
			return (i);
		i++;
	}
	return (i);
}

static size_t	end(char const *s1, char const *set)
{
	size_t	i;
	size_t	k;

	i = ft_strlen(s1);
	while (i > 0)
	{
		k = 0;
		while (set[k] != '\0')
		{
			if (s1[i] != set[k])
				k++;
			else
				break ;
		}
		if (set[k] == '\0' && s1[i] != set[k])
			return (ft_strlen(s1) - i - 1);
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	s;
	size_t	e;
	size_t	l;

	s = start(s1, set);
	e = end(s1, set);
	l = ft_strlen(s1) - s - e + 1;
	if (!s1 || !set)
		return (NULL);
	if (s == 0 && e == 0)
		return (ft_strdup(s1));
	if (s == ft_strlen(s1) && e == ft_strlen(s1))
		return (NULL);
	str = (char *)malloc(l * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, &s1[s], l);
	return (str);
}

/*int main()
{
	char *s1 = "lorem ipsum dolor sit amet";
	printf("%s\n", ft_strtrim(s1, "te"));
}*/