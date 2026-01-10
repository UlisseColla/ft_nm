/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:37:02 by ucolla            #+#    #+#             */
/*   Updated: 2023/10/20 15:47:52 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
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
	printf("%s\n", (char *)ft_lstlast(lst)->content);
	return (0);
}*/