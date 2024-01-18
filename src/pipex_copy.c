/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:53:25 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/18 19:10:32 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <pipex.h>
#include "../includes/Libft/libft.h"
#include "../includes/pipex.h"

void	debug_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		printf("\033[1;33m%-10s | %-15s | %-10d | %-10d\n\n\033[0m",
			cmd->cmd[0], cmd->path, cmd->position, cmd->is_env);
		for (int i = 0; cmd->cmd[i] != NULL; i++)
		{
			printf("\033[1;35m%-10s |\n\033[0m", cmd->cmd[i]);
		}
		cmd = cmd->next;
		printf("\033[1;32m-------------------DIVIDER--------------------\n\033[0m");
	}
}

void	debug_pipex(t_pipex *pipex)
{
	printf("\033[1;32m---------------------DEBUG--------------------\n\033[0m");
	printf("\033[1;32m%-30s | %d\n\033[0m", "Argc", pipex->argc);
	printf("\033[1;33m%-30s | %d\n\033[0m", "Total commands",
		pipex->total_cmds);
	printf("\033[1;34m%-30s | %d\n\033[0m", "Executed commands counter",
		pipex->executed_cmds_counter);
	printf("\033[1;35m%-30s | %d\n\033[0m", "Is heredoc", pipex->is_heredoc);
	printf("\033[1;36m%-30s | %s\n\033[0m", "Delimiter", pipex->delimiter);
	printf("\033[1;37m%-30s | %d\n\033[0m", "Is tempfile created",
		pipex->is_tempfile_created);
	printf("\033[1;32m%-30s | %s\n\033[0m", "Infile", pipex->infile);
	printf("\033[1;33m%-30s | %d\n\033[0m", "Infile fd", pipex->in_fd);
	printf("\033[1;34m%-30s | %s\n\033[0m", "Outfile", pipex->outfile);
	printf("\033[1;35m%-30s | %d\n\033[0m", "Outfile fd", pipex->out_fd);
	printf("\033[1;36m%-10s | %-10s | %-10s\n\033[0m", "Pipe", "Index",
		"Value");
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			printf("    \033[1;37m%-10s[%d][%d] | %-10d\n\033[0m", "Pipe", i, j,
				pipex->pipes[i][j]);
		}
	}
	printf("\033[1;32m--------------------COMMANDS------------------\n\033[0m");
	printf("\033[1;32m%-10s | %-15s | %-10s | %-10s\n\n\033[0m", "Command",
		"Path", "Position", "Is env");
	debug_cmd(pipex->commands);
}

void	ft_execute_cmd(t_cmd *cmd, char **envp)
{
	if (execve(cmd->path, cmd->cmd, envp) == -1)
		ft_error("execve failed");
}

// void	ft_child_process(t_pipex *pipex, char **envp)
// {
// 	ft_execute_cmd(pipex, ft_get_cmd_by_position(pipex->commands,
// 			pipex->executed_cmds_counter), envp);
// }

int	ft_pipex(char **argv, char **envp, t_pipex *pipex)
{
	pid_t	pid;

	ft_run_pipex(pipex, argv, envp);
	dup2(pipex->in_fd, STDIN_FILENO);
	while (pipex->executed_cmds_counter < pipex->total_cmds - 1)
	{
		if (pipe(pipex->pipes[pipex->executed_cmds_counter]) == -1)
			ft_error("pipe failed");
		//debug_pipex(pipex);
		pid = fork();
		if (pid == -1)
			ft_error("fork failed");
		if (pid == 0)
		{
			close(pipex->pipes[pipex->executed_cmds_counter][READ]);
			dup2(pipex->pipes[pipex->executed_cmds_counter][WRITE],
				STDOUT_FILENO);
			ft_execute_cmd(ft_get_cmd_by_position(pipex->commands,
					pipex->executed_cmds_counter), envp);
		}
		else
		{
			close(pipex->pipes[pipex->executed_cmds_counter][WRITE]);
			dup2(pipex->pipes[pipex->executed_cmds_counter][READ],
				STDIN_FILENO);
			waitpid(pid, NULL, 0);
			pipex->executed_cmds_counter++;
		}
	}
	dup2(pipex->out_fd, STDOUT_FILENO);
	ft_execute_cmd(ft_get_cmd_by_position(pipex->commands,
			pipex->executed_cmds_counter), envp);
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
	pipex->argc = argc;
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
