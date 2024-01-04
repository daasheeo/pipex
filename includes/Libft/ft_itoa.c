/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:57:29 by jesmunoz          #+#    #+#             */
/*   Updated: 2023/09/29 09:54:53 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_int_len(int num)
{
	int	count;

	count = 0;
	if (num != 0)
	{
		if (num < 0)
		{
			num *= -1;
			count++;
		}
		while (num != 0)
		{
			num /= 10;
			count++;
		}
	}
	else
		count = 1;
	return (count);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*str;
	int long	number;

	len = ft_int_len(n);
	number = n;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (number < 0)
	{
		str[0] = '-';
		number = -number;
	}
	if (number == 0)
		str[0] = '0';
	str[len--] = '\0';
	while (number)
	{
		str[len] = ((number % 10) + '0');
		number /= 10;
		len--;
	}
	return (str);
}
