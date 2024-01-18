/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:14:06 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/18 13:34:51 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libft/libft.h"
#include "../includes/pipex.h"

t_cmd	*ft_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		ft_error("malloc failed");
	new_cmd->name = NULL;
	new_cmd->cmd = NULL;
	new_cmd->path = NULL;
	new_cmd->position = 0;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	ft_add_cmd(t_cmd **cmd_list, t_cmd *cmd)
{
	t_cmd	*current_cmd;

	if (!cmd_list)
		ft_error("cmd_list is NULL");
	if (!*cmd_list)
	{
		*cmd_list = cmd;
		return ;
	}
	current_cmd = *cmd_list;
	while (current_cmd->next)
		current_cmd = current_cmd->next;
	current_cmd->next = cmd;
}

t_pipex	*ft_pipex_init(void)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex->argc = 0;
	pipex->total_cmds = 0;
	pipex->is_heredoc = false;
	pipex->delimiter = NULL;
	pipex->commands = NULL;
	pipex->executed_cmds_counter = 0;
	return (pipex);
}

t_cmd	*ft_get_cmd_by_position(t_cmd *cmd_list, int position)
{
	t_cmd	*current_cmd;

	current_cmd = cmd_list;
	while (current_cmd->position != position)
	{
		ft_putstr_fd("current_cmd->position: ", STDIN_FILENO);
		current_cmd = current_cmd->next;
	}
	return (current_cmd);
}

t_cmd	*ft_get_last_cmd(t_cmd *cmd_list)
{
	t_cmd	*current_cmd;

	current_cmd = cmd_list;
	while (current_cmd->next)
		current_cmd = current_cmd->next;
	return (current_cmd);
}
