/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:26:15 by jesmunoz          #+#    #+#             */
/*   Updated: 2023/09/21 10:57:25 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*csrc;
	char	*cdest;
	size_t	i;

	csrc = (char *)src;
	cdest = (char *)dst;
	i = 0;
	while (i < n)
	{
		if (cdest != NULL || csrc != NULL)
			cdest[i] = csrc[i];
		i++;
	}
	return ((void *)cdest);
}
