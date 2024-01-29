/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:53:45 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/29 17:12:39 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define TMP_FILE "temp_here_doc.txt"

/*----------------------------------------------------------------------------*/
/*--------------------------------ERROR-HANDLER-------------------------------*/
/*----------------------------------------------------------------------------*/

# define ERR_ENV "pipex: Invalid environment"
# define ERR_CMD "command not found"
# define ERR_ARG "pipex: Invalid arguments"
# define ERR_PIPE "pipex: pipe faillure"
# define ERR_FILE "pipex: file faillure"
# define ERR_FORK "pipex: fork faillure"
# define ERR_EXEC "pipex:execve faillure"
# define ERR_OPEN "pipex: input: No such file or directory"
# define ERR_CLOSE "pipex: close faillure"
# define ERR_DUP "pipex: dup2 faillure"
# define ERR_MALLOC "pipex: malloc faillure"
# define ERR_WAITPID "pipex: waitpid faillure"

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_fd
{
	READ,
	WRITE
}		t_fd;

/*----------------------------------------------------------------------------*/
/*-----------------------------------PROGRAM----------------------------------*/
/*----------------------------------------------------------------------------*/

char	*ft_getenv(const char *name, char **envp);
char	*ft_search_path(char *cmd, char **envp);
char	**ft_custom_split(char *string, char splitter, char flag);

/*----------------------------------------------------------------------------*/
/*--------------------------------MEMORY-&&-EXIT------------------------------*/
/*----------------------------------------------------------------------------*/

void	ft_free_cmd(char **cmd_args);
void	ft_exit_error(int error_code, char *message, char **cmd);
void	free_lst_memory(char **str);

#endif