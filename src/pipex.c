/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:39:38 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/29 17:37:57 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../libs/Libft/libft.h"

void	ft_execute_cmd(char *cmd, char **envp)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_args = NULL;
	if (ft_strncmp(cmd, "awk ", 4) == 0 && ft_strchr(cmd, '\''))
		cmd_args = ft_custom_split(cmd, ' ', '\'');
	else if (ft_strncmp(cmd, "awk ", 4) == 0 && ft_strchr(cmd, '\"'))
		cmd_args = ft_custom_split(cmd, ' ', '\"');
	else
		cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		ft_exit_error(1, ERR_MALLOC, NULL);
	cmd_path = ft_search_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		ft_exit_error(127, ERR_CMD, cmd_args);
	}
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		free(cmd_path);
		ft_free_cmd(cmd_args);
		ft_exit_error(126, ERR_EXEC, NULL);
	}
}

int	ft_get_fd(char *file, int option)
{
	int	fd;

	fd = 0;
	if (option == 0)
		fd = open(file, O_RDONLY, 0777);
	else if (option == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_exit_error(0, ERR_OPEN, NULL);
	return (fd);
}

void	ft_child_process(int p_fd[2], char **argv, char **envp, int fd)
{
	dup2(fd, STDIN_FILENO);
	dup2(p_fd[WRITE], STDOUT_FILENO);
	close(p_fd[READ]);
	close(fd);
	ft_execute_cmd(argv[2], envp);
}

void	ft_parent_process(int p_fd[2], char **argv, char **envp, int fd)
{
	pid_t	pid;
	int		status;

	dup2(fd, STDOUT_FILENO);
	dup2(p_fd[READ], STDIN_FILENO);
	close(p_fd[WRITE]);
	close(fd);
	pid = fork();
	if (pid == -1)
		ft_exit_error(1, ERR_FORK, NULL);
	if (pid == 0)
		ft_execute_cmd(argv[3], envp);
	if (wait(&status) == pid)
		exit(status / 256);
}

int	main(int argc, char **argv, char **envp)
{
	int		p_fd[2];
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		ft_exit_error(1, ERR_ARG, NULL);
	if (envp == NULL)
		ft_exit_error(1, ERR_ENV, NULL);
	if (pipe(p_fd) == -1)
		ft_exit_error(1, ERR_PIPE, NULL);
	fd[0] = ft_get_fd(argv[1], STDIN_FILENO);
	fd[1] = ft_get_fd(argv[4], STDOUT_FILENO);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
		ft_child_process(p_fd, argv, envp, fd[0]);
	ft_parent_process(p_fd, argv, envp, fd[1]);
}
