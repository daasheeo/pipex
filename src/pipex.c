/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:53:25 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/17 15:20:41 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <pipex.h>
#include "../includes/Libft/libft.h"
#include "../includes/pipex.h"

void	debug_cmd(t_cmd *cmd)
{
	printf("Command name: %s\n", cmd->name);
	printf("Command path: %s\n", cmd->path);
	printf("Command position: %d\n", cmd->position);
	printf("Is env: %d\n", cmd->is_env);
	printf("Command arguments:\n");
	for (int i = 0; cmd->cmd[i] != NULL; i++)
	{
		printf("    %s\n", cmd->cmd[i]);
	}
	if (cmd->next != NULL)
	{
		printf("Next command:\n");
		debug_cmd(cmd->next);
	}
}

void	debug_pipex(t_pipex *pipex)
{
	printf("------DEBUG-----\n");
	printf("Total commands: %d\n", pipex->total_cmds);
	printf("Executed commands counter: %d\n", pipex->executed_cmds_counter);
	printf("Is heredoc: %d\n", pipex->is_heredoc);
	printf("Delimiter: %s\n", pipex->delimiter);
	printf("Is tempfile created: %d\n", pipex->is_tempfile_created);
	printf("Infile: %s\n", pipex->infile);
	printf("Infile fd: %d\n", pipex->in_fd);
	printf("Outfile: %s\n", pipex->outfile);
	printf("Outfile fd: %d\n", pipex->out_fd);
	printf("Pipes:\n");
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			printf("    Pipe[%d][%d]: %d\n", i, j, pipex->pipes[i][j]);
		}
	}
	printf("Commands:\n");
	debug_cmd(pipex->commands);
}

void	ft_execute_cmd(t_pipex *pipex, t_cmd *cmd, char **envp)
{
	debug_pipex(pipex);
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
	execve(cmd->path, cmd->cmd, envp);
	ft_close_pipes(pipex);
}

void	ft_child_process(t_pipex *pipex, char **envp)
{
	ft_execute_cmd(pipex, ft_get_cmd_by_position(pipex->commands,
			pipex->executed_cmds_counter), envp);
}

int	ft_pipex(char **argv, char **envp, t_pipex *pipex)
{
	pid_t	pid;

	ft_run_pipex(pipex, argv, envp);
	ft_create_pipes(pipex);
	while (pipex->executed_cmds_counter < pipex->total_cmds)
	{
		pid = fork();
		printf("pid-> %d\n", pid);
		if (pid < 0)
			ft_error("fork failed");
		if (pid == 0)
		{
			ft_child_process(pipex, envp);
		}
		else
		{
			waitpid(-1, NULL, 0);
			pipex->executed_cmds_counter++;
		}
	}
	ft_close_pipes(pipex);
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
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		pipex->is_heredoc = true;
		pipex->delimiter = argv[2];
		pipex->total_cmds = argc - 4;
	}
	ft_get_infile_fd(pipex);
	ft_get_outfile_fd(pipex);
	ft_pipex(argv, envp, pipex);
	ft_free_pipex(pipex);
	return (0);
}
