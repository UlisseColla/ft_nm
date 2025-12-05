/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 11:31:05 by ucolla            #+#    #+#             */
/*   Updated: 2023/11/05 14:47:47 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(uintptr_t ptr, char *base)
{
	int				k;
	int				l;
	int				ptr_to_print[20];

	k = 0;
	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	while (ptr)
	{
		ptr_to_print[k] = ptr % 16;
		ptr /= 16;
		k++;
	}
	l = k;
	write(1, "0x", 2);
	while (--k >= 0)
		ft_putchar(base[ptr_to_print[k]]);
	return (l + 2);
}
/* int main()
{
	ft_putptr(0, "0123456789abcdef");
	printf("\n");
	printf("%p\n", 0);
} */