/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:53:25 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/08 16:11:34 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <pipex.h>
#include "../includes/Libft/libft.h"
#include "../includes/pipex.h"

void	ft_execute_cmd(t_pipex *pipex, t_cmd *cmd, char **envp)
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

void	ft_child_process(t_pipex *pipex, int *end, char **envp)
{
	int	f1;

	if (pipex->executed_cmds_counter == pipex->total_cmds - 1)
	{
		f1 = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		pipex->in_fd = f1;
		pipex->out_fd = end[1];
	}
	else
	{
		f1 = open(pipex->infile, O_RDONLY);
		pipex->in_fd = f1;
		pipex->out_fd = end[1];
	}
	if (f1 < 0)
		ft_error("open failed");
	ft_execute_cmd(pipex, ft_get_cmd_by_position(pipex->commands,
			pipex->executed_cmds_counter), envp);
	close(f1);
	close(end[1]);
}

void	ft_parent_process(t_pipex *pipex, int *end, pid_t pid)
{
	int	status;
	// ft_execute_cmd(pipex, ft_get_last_cmd(pipex->commands), envp);
	if (pipex->executed_cmds_counter == 0)
		close(end[WRITE]);
	close(end[READ]);
	waitpid(pid, &status, 0);
}

int	ft_pipex(char **argv, char **envp, t_pipex *pipex)
{
	pid_t	pid;
	int		end[2];

	while (pipex->executed_cmds_counter < pipex->total_cmds)
	{
		if (pipe(end) == -1)
			ft_error("pipe failed");
		pid = fork();
		if (pid < 0)
			ft_error("fork failed");
		if (pid == 0)
		{
			if (pipex->executed_cmds_counter == 0)
				ft_run_pipex(pipex, argv, envp);
			ft_child_process(pipex, end, envp);
		}
		else
			ft_parent_process(pipex, end, pid);
		pipex->executed_cmds_counter++;
	}
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
	pipex->outfile = argv[4];
	ft_pipex(argv, envp, pipex);
	return (0);
}
