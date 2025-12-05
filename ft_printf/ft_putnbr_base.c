/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 21:34:33 by ucolla            #+#    #+#             */
/*   Updated: 2023/11/05 15:25:13 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(unsigned int nbr, char *base)
{
	int				k;
	int				l;
	int				nbr_to_print[20];

	k = 0;
	if (nbr == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	while (nbr)
	{
		nbr_to_print[k] = nbr % 16;
		nbr /= 16;
		k++;
	}
	l = k;
	while (--k >= 0)
		ft_putchar(base[nbr_to_print[k]]);
	return (l);
}
