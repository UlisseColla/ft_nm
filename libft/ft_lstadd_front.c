/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:41:28 by ucolla            #+#    #+#             */
/*   Updated: 2023/10/20 17:57:45 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *nw)
{
	if (!nw)
		return ;
	nw->next = *lst;
	*lst = nw;
}

/*int main()
{
	t_list *lst;
	t_list *nw;

	lst = ft_lstnew("Hello");
	nw = ft_lstnew("World");
	ft_lstadd_front(&lst, nw);
	printf("%s\n", (char *)lst->content);
	printf("%s\n", (char *)lst->next->content);
	return (0);
}*/