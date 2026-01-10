/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:56:25 by ucolla            #+#    #+#             */
/*   Updated: 2023/10/20 15:39:25 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}

/*void	ft_del(void *content)
{
	free(content);
}

int main()
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
	ft_lstadd_back(&lst, n1);
	ft_lstadd_back(&lst, n2);
	ft_lstadd_back(&lst, n3);
	ft_lstadd_back(&lst, n4);
	ft_lstdelone(n4, &ft_del);
	while(lst)
	{
		printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
	return (0);
}*/