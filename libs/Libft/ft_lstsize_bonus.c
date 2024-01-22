/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:52:51 by jesmunoz          #+#    #+#             */
/*   Updated: 2023/09/19 09:52:54 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	if (!lst)
		return (0);
	return (1 + ft_lstsize(lst->next));
}

// int	ft_lstsize(t_list *lst)
// {
// 	int	i;

// 	i = 0;
// 	if (!lst)
// 		return (0);
// 	while (lst)
// 	{
// 		lst = lst->next;
// 		i++;
// 	}
// 	return (i);
// }
