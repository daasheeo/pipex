/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 20:01:48 by jesmunoz          #+#    #+#             */
/*   Updated: 2023/09/18 09:41:09 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	to_find_len;

	i = 0;
	to_find_len = ft_strlen(to_find);
	if (to_find_len == 0)
		return ((char *)str);
	while (str[i] != '\0' && i + to_find_len <= len)
	{
		if (ft_strncmp(str + i, to_find, to_find_len) == 0)
			return ((char *)str + i);
		i++;
	}
	return (0);
}
