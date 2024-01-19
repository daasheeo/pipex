/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:21:17 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/18 20:03:09 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libft/libft.h"
#include "../includes/pipex.h"

void	ft_run_pipex(t_pipex *pipex_data, char **argv, char **env_vars)
{
	int		command_index;
	int		command_position;
	t_cmd	*current_command;

	command_index = 2;
	command_position = 0;
	if (pipex_data->is_heredoc)
	{
		ft_text_to_file(pipex_data->delimiter, pipex_data->in_fd);
		ft_get_infile_fd(pipex_data);
		command_index = 3;
	}
	current_command = NULL;
	while (command_index < pipex_data->argc - 1)
	{
		current_command = ft_new_cmd();
		ft_putstr_fd(argv[command_index], 1);
		ft_putstr_fd("\n", 1);
		current_command->cmd = ft_split(argv[command_index], ' ');
		current_command->name = ft_split(argv[command_index], ' ')[0];
		current_command->path = ft_search_path(current_command->name, env_vars);
		current_command->position = command_position;
		ft_add_cmd(&pipex_data->commands, current_command);
		command_index++;
		command_position++;
	}
}
