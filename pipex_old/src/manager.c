/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:16:01 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/22 10:17:31 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libft/libft.h"
#include "../includes/pipex.h"

void	ft_error(char *msg)
{
	printf("%s: %s\n", msg, strerror(errno));
	exit(1);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd == NULL)
	{
		return ;
	}
	free_cmd(cmd->next);
	free(cmd->name);
	i = 0;
	while (cmd->cmd[i] != NULL)
	{
		free(cmd->cmd[i]);
		i++;
	}
	free(cmd->cmd);
	free(cmd->path);
	free(cmd);
}

void	ft_free_pipex(t_pipex *pipex, char *msg)
{
	if (pipex == NULL)
	{
		return ;
	}
	if (pipex->is_heredoc)
		unlink(TMP_FILE);
	free_cmd(pipex->commands);
	free(pipex);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(strerror(errno), 2);
	exit(1);
}
