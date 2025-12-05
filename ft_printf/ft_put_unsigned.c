/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 11:47:16 by ucolla            #+#    #+#             */
/*   Updated: 2023/11/05 15:25:07 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_unsigned(unsigned int n)
{
	int		i;
	int		j;
	char	print[20];

	i = 0;
	if (n == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	while (n > 0)
	{
		print[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	j = i;
	i--;
	while (i >= 0)
	{
		write(1, &print[i], 1);
		i--;
	}
	return (j);
}
