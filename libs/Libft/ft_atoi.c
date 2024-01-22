/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:24:53 by jesmunoz          #+#    #+#             */
/*   Updated: 2023/12/30 18:14:26 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	short				parity;
	long long int		number;

	parity = 1;
	number = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			parity = -1;
		++str;
	}
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + *str - '0';
		++str;
		if (number < INT_MIN && parity == -1)
			return (0);
		if (number > INT_MAX && parity == 1)
			return (-1);
	}
	return (number * parity);
}
