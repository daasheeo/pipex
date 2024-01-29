/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:33:25 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/29 17:15:32 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../libs/Libft/libft.h"

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

void	ft_exit_error(int option, char *message, char **cmd)
{
	if (cmd && *cmd != NULL)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(message, STDERR_FILENO);
		ft_free_cmd(cmd);
	}
	else
		ft_putendl_fd(message, STDERR_FILENO);
	fprintf(stdout, "Error: %s\n", strerror(errno));
	if (option == 1)
		exit(1);
	else if (option == 126)
		exit(126);
	else if (option == 127)
		exit(127);
	else
		exit(0);
}



void	free_lst_memory(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
