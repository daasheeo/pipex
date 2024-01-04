/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:21:17 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/04 18:17:08 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libft/libft.h"
#include "../includes/pipex.h"

void	ft_run_pipex(t_pipex *pipex_data, char **argv, char **env_vars)
{
	int		command_index;
	t_cmd	*current_command;

	command_index = 0;
	while (command_index < pipex_data->total_cmds)
	{
		current_command = ft_new_cmd();
		current_command->cmd = ft_split(argv[command_index + 2], ' ');
		current_command->name = ft_split(argv[command_index + 2], ' ')[0];
		current_command->path = ft_search_path(current_command->name, env_vars);
		current_command->position = command_index;
		current_command->is_env = (current_command->path == NULL);
		current_command->is_last = (command_index == pipex_data->total_cmds
				- 1);
		current_command->is_child = (command_index == 0);
		ft_add_cmd(&pipex_data->commands, current_command);
		command_index++;
	}
}
