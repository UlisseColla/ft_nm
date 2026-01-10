/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:04:57 by ucolla            #+#    #+#             */
/*   Updated: 2023/10/17 14:03:29 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		k;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		k = 0;
		while (big[i + k] == little[k] && (i + k) < len)
		{
			if (little[k + 1] == '\0')
				return ((char *)(big + i));
			k++;
		}
		i++;
	}
	return (NULL);
}

/*int main()
{
	char *big = "lorem ipsum dolor sit amet";
	char *ret;

	ret = ft_strnstr(big, "", 10);
	printf("%s\n", ret);
	return (0);
}*/