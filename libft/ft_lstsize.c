/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:21:29 by ucolla            #+#    #+#             */
/*   Updated: 2023/10/20 15:39:52 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/*int main()
{
	t_list *lst;
	t_list *n1;
	t_list *n2;
	t_list *n3;
	t_list *n4;

	lst = ft_lstnew("Hello");
	n1 = ft_lstnew("one");
	n2 = ft_lstnew("two");
	n3 = ft_lstnew("three");
	n4 = ft_lstnew("four");
	
	ft_lstadd_front(&lst, n4);
	ft_lstadd_front(&lst, n3);
	ft_lstadd_front(&lst, n2);
	ft_lstadd_front(&lst, n1);
	printf("%d\n", ft_lstsize(lst));
	while (lst)
	{
		printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
	return (0);
}*/