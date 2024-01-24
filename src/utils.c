/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:33:25 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/23 14:59:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/Libft/libft.h"
#include "../include/pipex.h"

void	ft_free_cmd(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i])
	{
		free(cmd_args[i]);
		i++;
	}
	free(cmd_args);
}

void	ft_exit_error(int option, char *message)
{
	perror(message);
	if (option == 1)
		exit(1);
	if (option == 2)
		exit(127);
	exit(0);
}
