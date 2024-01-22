/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:15:22 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/22 11:58:58 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/Libft/libft.h"
#include "../include/pipex.h"

char	*ft_getenv(const char *name, char **envp)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == name[j] && j < len)
			j++;
		if (j == len && envp[i][j] == '=')
			return (&envp[i][j + 1]);
		i++;
	}
	return (NULL);
}
