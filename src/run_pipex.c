/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:21:17 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/17 10:04:42 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libft/libft.h"
#include "../includes/pipex.h"

void	ft_run_pipex(t_pipex *pipex_data, char **argv, char **env_vars)
{
	int		command_index;
	t_cmd	*current_command;
	int		total_commands;

	command_index = 0;
	total_commands = pipex_data->total_cmds;
	if (pipex_data->is_heredoc)
	{
		ft_text_to_file(pipex_data->delimiter, pipex_data->in_fd);
		ft_get_infile_fd(pipex_data);
		command_index = 1;
	}
	current_command = NULL;
	while (command_index <= total_commands)
	{
		current_command = ft_new_cmd();
		current_command->cmd = ft_split(argv[command_index + 2], ' ');
		current_command->name = ft_split(argv[command_index + 2], ' ')[0];
		current_command->path = ft_search_path(current_command->name, env_vars);
		current_command->position = command_index;
		ft_add_cmd(&pipex_data->commands, current_command);
		command_index++;
	}
}
