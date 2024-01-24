/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:53:45 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/23 14:56:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define TMP_FILE "temp_here_doc.txt"

# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>

typedef enum e_fd
{
	READ,
	WRITE
}					t_fd;

/*------------------------------------------------------------------------------*/
/*-----------------------------------PROGRAM------------------------------------*/
/*------------------------------------------------------------------------------*/

char				*ft_getenv(const char *name, char **envp);
char				*ft_search_path(char *cmd, char **envp);
char 				**ft_custom_split(char *string, char splitter, char flag);

/*------------------------------------------------------------------------------*/
/*--------------------------------MEMORY-&&-EXIT--------------------------------*/
/*------------------------------------------------------------------------------*/

void 				ft_free_cmd(char **cmd_args);
void 				ft_exit_error(int error_code, char *message);

#endif