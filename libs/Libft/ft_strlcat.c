/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:41:39 by jesmunoz          #+#    #+#             */
/*   Updated: 2023/09/15 10:20:17 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	length;
	size_t	i;

	i = 0;
	length = ft_strlen(dst);
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize < 1)
		return (dstsize + src_len);
	while (src[i] && length < dstsize - 1)
	{
		dst[length] = src[i];
		i++;
		length++;
	}
	dst[length] = '\0';
	if (dstsize < dst_len)
		return (src_len + dstsize);
	else
		return (dst_len + src_len);
}
