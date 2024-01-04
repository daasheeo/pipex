/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:53:25 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/04 18:13:05 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <pipex.h>
#include "../includes/Libft/libft.h"
#include "../includes/pipex.h"

void	ft_execute_cmd(t_pipex *pipex, t_cmd *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (pipex->in_fd != STDIN_FILENO)
		{
			dup2(pipex->in_fd, STDIN_FILENO);
			close(pipex->in_fd);
		}
		if (pipex->out_fd != STDOUT_FILENO)
		{
			dup2(pipex->out_fd, STDOUT_FILENO);
			close(pipex->out_fd);
		}
		if (cmd->is_env)
			execve(cmd->path, cmd->cmd, envp);
		else
			execve(cmd->path, cmd->cmd, NULL);
		ft_error("execve failed");
	}
	else if (pid < 0)
		ft_error("fork failed");
}

void	ft_child_process(t_pipex *pipex, int *end, char **envp)
{
	int	f1;

	f1 = open(pipex->infile, O_RDONLY);
	if (f1 < 0)
		ft_error("open failed");
	pipex->in_fd = f1;
	dup2(f1, STDIN_FILENO);
	close(f1);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	pipex->executed_cmds_counter++;
	if (execve(ft_get_path_by_position(pipex->commands,
				pipex->executed_cmds_counter),
			ft_get_cmd_by_position(pipex->commands,
				pipex->executed_cmds_counter)->cmd, envp) == -1)
		ft_error("execve failed");
	exit(EXIT_FAILURE);
}

void	ft_parent_process(t_pipex *pipex, int *end, char **envp)
{
	int	status;
	int	f2;

	waitpid(-1, &status, 0);
	f2 = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (f2 < 0)
		ft_error("open failed");
	pipex->out_fd = f2;
	dup2(end[0], STDIN_FILENO);
	close(end[1]);
	dup2(f2, STDOUT_FILENO);
	close(f2);
	if (pipex->executed_cmds_counter == pipex->total_cmds)
	{
		if (execve(ft_get_last_cmd(pipex->commands)->path,
				ft_get_last_cmd(pipex->commands)->cmd, envp) == -1)
			ft_error("execve failed");
	}
}

int	ft_pipex(char **argv, char **envp, t_pipex *pipex)
{
	int		end[2];
	pid_t	parent;

	if (pipe(end) == -1)
		ft_error("pipe failed");
	ft_run_pipex(pipex, argv, envp);
	parent = fork();
	if (parent < 0)
		return (1);
	if (!parent)
	{
		printf("child\n");
		ft_child_process(pipex, end, envp);
	}
	else
	{
		printf("parent\n");
		ft_parent_process(pipex, end, envp);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc != 5)
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
	pipex->outfile = argv[4];
	ft_pipex(argv, envp, pipex);
	return (0);
}
