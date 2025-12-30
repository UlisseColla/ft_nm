/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:14:25 by ucolla            #+#    #+#             */
/*   Updated: 2023/10/20 18:49:59 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	divide_by_ten(int n)
{
	size_t	j;

	j = 1;
	if (n < 0)
	{
		n *= (-1);
		j++;
	}
	while (n > 9)
	{
		n /= 10;
		j++;
	}
	return (j);
}

static char	*f(int n)
{
	size_t	k;
	char	*number;

	k = divide_by_ten(n);
	number = (char *)malloc((k + 1) * sizeof(char));
	if (number == NULL)
		return (NULL);
	if (n < 0)
	{
		number[0] = '-';
		n = -n;
	}
	number[k] = '\0';
	while (k-- > 0 && n > 0)
	{
		number[k] = (n % 10) + 48;
		n /= 10;
	}
	return (number);
}

char	*ft_itoa(int n)
{
	char	*number;

	if (n == -2147483648)
		number = ft_strdup("-2147483648");
	else if (n == 0)
		number = ft_strdup("0");
	else
		number = f(n);
	return (number);
}

/*int main()
{
	printf("%s\n", ft_itoa(10));
	printf("%s\n", ft_itoa(-10));
	printf("%s\n", ft_itoa(-9));
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(8124));
	printf("%s\n", ft_itoa(-2147483647));
	printf("%d", divide_by_ten(-12453));
}*/