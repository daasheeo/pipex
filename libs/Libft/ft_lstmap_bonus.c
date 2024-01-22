/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:15:45 by jesmunoz          #+#    #+#             */
/*   Updated: 2023/09/21 17:41:11 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*elem;
	void	*temp;

	if (!lst)
		return (0);
	new = 0;
	while (lst)
	{
		temp = (*f)(lst->content);
		elem = ft_lstnew(temp);
		if (!elem)
		{
			del(temp);
			return (ft_lstclear(&new, del), NULL);
		}
		ft_lstadd_back(&new, elem);
		lst = lst->next;
	}
	return (new);
}
