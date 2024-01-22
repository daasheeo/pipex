/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:53:45 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/22 11:56:51 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define TMP_FILE "temp_here_doc.txt"

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
}					t_fd;

typedef struct s_cmd
{
	char			*name;
	char			**cmd;
	char			*path;
	int				position;
	struct s_cmd	*next;

}					t_cmd;

typedef struct s_pipex
{
	t_cmd			*commands;
	int				argc;
	int				total_cmds;
	int				executed_cmds_counter;
	bool			is_heredoc;
	char			*delimiter;
	bool			is_tempfile_created;
	const char		*infile;
	int				in_fd;
	const char		*outfile;
	int				out_fd;
	int				pipes[2][2];
}					t_pipex;

char				*ft_getenv(const char *name, char **envp);
void				ft_error(char *msg);
char				*ft_search_path(char *cmd, char **envp);
t_pipex				*ft_pipex_init(int argc, char **argv);
void				ft_add_cmd(t_cmd **cmd_list, t_cmd *cmd);
t_cmd				*ft_new_cmd(void);
void				ft_run_pipex(t_pipex *pipex_data, char **argv,
						char **env_vars);
t_cmd				*ft_get_cmd_by_position(t_cmd *cmd_list, int position);
void				ft_get_infile_fd(t_pipex *pipex);
void				ft_get_outfile_fd(t_pipex *pipex);
void				ft_free_pipex(t_pipex *pipex, char *msg);
void				ft_text_to_file(char *delimiter, int fd);
char				*get_next_line(int fd);

void 				ft_free_cmd(char **cmd_args);
void 				ft_exit_error(int error_code);

#endif