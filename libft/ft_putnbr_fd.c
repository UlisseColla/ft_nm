/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:19:50 by ucolla            #+#    #+#             */
/*   Updated: 2023/10/19 12:50:56 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	c = (n % 10) + '0';
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = n * -1;
		if (n < 10)
		{
			c = (n % 10) + '0';
			write(fd, &c, 1);
			return ;
		}
		ft_putnbr_fd(n / 10, fd);
	}
	else if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
}

/*int main()
{
	ft_putnbr_fd(-12345, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(12345, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(-1, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(2, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(-1000, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(12000, 1);
	write(1, "\n", 1);
	return (0);
}*/