/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:39:38 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/25 13:10:29 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../libs/Libft/libft.h"

void	ft_execute_cmd(char *cmd, char **envp, char ***cmd_args)
{
	char	*cmd_path;

	if (ft_strncmp(cmd, "awk ", 4) == 0 && ft_strchr(cmd, '\''))
		*cmd_args = ft_custom_split(cmd, ' ', '\'');
	else if (ft_strncmp(cmd, "awk ", 4) == 0 && ft_strchr(cmd, '\"'))
		*cmd_args = ft_custom_split(cmd, ' ', '\"');
	else
		*cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		ft_exit_error(1, "pipex: ft_split");
	cmd_path = ft_search_path(*cmd_args[0], envp);
	if (!cmd_path)
	{
		ft_free_cmd(*cmd_args);
		ft_exit_error(2, "pipex: command not found");
	}
	execve(cmd_path, *cmd_args, envp);
	ft_exit_error(1, "pipex: execve");
}

int	ft_get_fd(char *file, int option)
{
	int	fd;

	fd = 0;
	if (option == 0)
		fd = open(file, O_RDONLY, 0777);
	else if (option == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ft_exit_error(1, "pipex: input");
	return (fd);
}

void	ft_child_process(int p_fd[2], char **argv, char **envp,
		char ***cmd_args)
{
	int	fd;

	fd = ft_get_fd(argv[1], STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	dup2(p_fd[WRITE], STDOUT_FILENO);
	close(p_fd[READ]);
	ft_execute_cmd(argv[2], envp, cmd_args);
}

void	ft_parent_process(int p_fd[2], char **argv, char **envp, char ***cmd_args)
{
	int		fd;
	pid_t	pid;

	fd = ft_get_fd(argv[4], STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	dup2(p_fd[READ], STDIN_FILENO);
	close(p_fd[WRITE]);
	pid = fork();
	if (pid == -1)
		ft_exit_error(1, "pipex: fork");
	if (pid == 0)
		ft_execute_cmd(argv[3], envp, cmd_args);
	waitpid(pid, NULL, 0);
}
void	ft_leaks(void)
{
	system("leaks -q pipex");
}

int	main(int argc, char **argv, char **envp)
{
	int		p_fd[2];
	pid_t	pid;
	char	**cmd_args;

	// atexit(ft_leaks);
	if (argc != 5)
		ft_exit_error(1, "pipex: invalid arguments");
	if (pipe(p_fd) == -1)
		exit(-1);
	cmd_args = ft_calloc(1, sizeof(char **));
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
		ft_child_process(p_fd, argv, envp, &cmd_args);
	ft_parent_process(p_fd, argv, envp, &cmd_args);
	ft_free_cmd(cmd_args);
}
