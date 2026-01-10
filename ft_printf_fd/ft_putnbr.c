/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:19:50 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/21 18:17:13 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

int	ft_putnbr(long n, int fd)
{
	int		i;
	char	c;

	i = n;
	if (n < 0)
	{
		write(fd, "-", 1);
		n = n * -1;
		if (n < 10)
		{
			c = (n % 10) + '0';
			write(fd, &c, 1);
			return (ft_count_digits(i));
		}
		ft_putnbr(n / 10, fd);
	}
	else if (n > 9)
		ft_putnbr(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
	return (ft_count_digits(i));
}

/* int main()
{
	printf("valore di count_digits: %d\n", ft_putnbr(-12345));
	write(1, "\n", 1);
	printf("valore di count_digits: %d\n", ft_putnbr(45));
	write(1, "\n", 1);
	printf("valore di count_digits: %d\n", ft_putnbr(-345));
	write(1, "\n", 1);
	printf("valore di count_digits: %d\n", ft_putnbr(0));
	write(1, "\n", 1);
	printf("valore di count_digits: %d\n", ft_putnbr(-1));
	write(1, "\n", 1);
	printf("valore di count_digits: %d\n", ft_putnbr(1));
	write(1, "\n", 1);
	ft_putnbr(-1);
	return (0);
} */