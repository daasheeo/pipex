/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:39:38 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/22 11:59:19 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/Libft/libft.h"
#include "../include/pipex.h"


void ft_execute_cmd(char *cmd, char **envp)
{
    char **cmd_args;
    char *cmd_path;
    
    cmd_args = ft_split(cmd, ' ');
    cmd_path = ft_search_path(cmd_args[0], envp);
    if (execve(cmd_path, cmd_args, envp) == -1)
    {
        ft_putstr_fd("Error: Command not found\n", 2);
        ft_putendl_fd(cmd_args[0], 2);
        ft_free_cmd(cmd_args);
        exit(0);
    }
}

int ft_get_fd(char *file, int option)
{
    int fd;
    
    if (option == 0)
        fd = open(file, O_RDONLY, 0777);
    else if (option == 1)
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        ft_exit_error(0);
    return (fd);
}

void ft_child_process(int p_fd[2], char **argv, char **envp)
{
    int fd;
    
    fd = ft_get_fd(argv[1], STDIN_FILENO);
    dup2(fd, STDIN_FILENO);
    dup2(p_fd[WRITE], STDOUT_FILENO);
    close(p_fd[READ]);
    ft_execute_cmd(argv[2], envp);
}

void ft_parent_process(int p_fd[2], char **argv, char **envp)
{
    int fd;
    fd = ft_get_fd(argv[4], STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(p_fd[READ], STDIN_FILENO);
    close(p_fd[WRITE]);
    ft_execute_cmd(argv[3], envp);
}

int main (int argc, char **argv, char **envp)
{
    int p_fd[2];
    pid_t pid;
    
    if (argc != 5)
        ft_exit_error(1);
    if (pipe(p_fd) == -1)
        exit(-1);
    pid = fork();
    if (pid == -1)
        exit(-1);
    if (pid == 0)
        ft_child_process(p_fd, argv, envp);
    ft_parent_process(p_fd, argv, envp);
}