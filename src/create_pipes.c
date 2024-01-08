/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:17:48 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/08 17:22:17 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->total_cmds - 1)
	{
		if (pipe(pipex->pipes[i]) < 0)
			ft_error("pipe failed");
		i++;
	}
}

void	ft_close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->total_cmds - 1)
	{
		close(pipex->pipes[i][READ]);
		close(pipex->pipes[i][WRITE]);
		i++;
	}
}