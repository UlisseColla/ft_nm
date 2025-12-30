/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:10:37 by ucolla            #+#    #+#             */
/*   Updated: 2023/10/17 14:17:32 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int			counter_minus;
	int			i;
	long int	c;

	counter_minus = 0;
	i = 0;
	c = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		counter_minus++;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		c = (c * 10) + (nptr[i] - '0');
		i++;
	}
	if (counter_minus == 1)
		c = -c;
	return (c);
}

/*int main()
{
	printf("%d\n", ft_atoi("-1234"));
	printf("%d\n", atoi("-1234"));
	return (0);
}*/