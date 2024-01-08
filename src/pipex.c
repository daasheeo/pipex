/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:53:25 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/08 19:17:29 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <pipex.h>
#include "../includes/Libft/libft.h"
#include "../includes/pipex.h"

void	ft_execute_cmd(t_pipex *pipex, t_cmd *cmd, char **envp)
{
	if (pipex->executed_cmds_counter == 0)
	{
		dup2(pipex->in_fd, STDIN_FILENO);
		dup2(pipex->pipes[pipex->executed_cmds_counter][WRITE], STDOUT_FILENO);
	}
	else if (pipex->executed_cmds_counter == pipex->total_cmds - 1)
	{
		dup2(pipex->pipes[pipex->executed_cmds_counter - 1][READ],
			STDIN_FILENO);
		dup2(pipex->out_fd, STDOUT_FILENO);
	}
	else
	{
		dup2(pipex->pipes[pipex->executed_cmds_counter - 1][READ],
			STDIN_FILENO);
		dup2(pipex->pipes[pipex->executed_cmds_counter][WRITE], STDOUT_FILENO);
	}
	ft_close_pipes(pipex);
	if (cmd->is_env)
		execve(cmd->path, cmd->cmd, envp);
	else
		execve(cmd->path, cmd->cmd, NULL);
}

void	ft_child_process(t_pipex *pipex, char **envp)
{
	ft_execute_cmd(pipex, ft_get_cmd_by_position(pipex->commands,
			pipex->executed_cmds_counter), envp);
}

void	ft_parent_process(t_pipex *pipex)
{
	ft_close_pipes(pipex);
	waitpid(-1, NULL, 0);
}

int	ft_pipex(char **argv, char **envp, t_pipex *pipex)
{
	pid_t	pid;

	ft_run_pipex(pipex, argv, envp);
	ft_create_pipes(pipex);
	while (pipex->executed_cmds_counter < pipex->total_cmds)
	{
		pid = fork();
		if (pid < 0)
			ft_error("fork failed");
		if (pid == 0)
			ft_child_process(pipex, envp);
		pipex->executed_cmds_counter++;
	}
	ft_parent_process(pipex);
	return (0);
}


int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc < 5)
	{
		printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	pipex = NULL;
	pipex = ft_pipex_init();
	if (!pipex)
		ft_error("malloc failed");
	pipex->total_cmds = argc - 3;
	pipex->infile = argv[1];
	pipex->outfile = argv[argc - 1];
	ft_get_infile_fd(pipex);
	ft_get_outfile_fd(pipex);
	ft_pipex(argv, envp, pipex);
	ft_free_pipex(pipex);
	return (0);
}
