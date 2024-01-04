/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:53:45 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/04 18:10:03 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_cmd
{
	char			*name;
	char			**cmd;
	char			*path;
	int				position;
	bool			is_env;
	bool			is_child;
	bool			is_last;
	struct s_cmd	*next;

}					t_cmd;

typedef struct s_pipex
{
	t_cmd			*commands;
	int				total_cmds;
	int				executed_cmds_counter;
	bool			is_heredoc;
	const char		*infile;
	int				in_fd;
	const char		*outfile;
	int				out_fd;
}					t_pipex;

char				*ft_getenv(const char *name, char **envp);
void				ft_error(char *msg);
char				*ft_search_path(char *cmd, char **envp);
t_pipex				*ft_pipex_init(void);
void				ft_add_cmd(t_cmd **cmd_list, t_cmd *cmd);
t_cmd				*ft_new_cmd(void);
void				ft_run_pipex(t_pipex *pipex_data, char **argv,
						char **env_vars);
t_cmd				*ft_get_last_cmd(t_cmd *cmd_list);
t_cmd				*ft_get_cmd_by_position(t_cmd *cmd_list, int position);
char				*ft_get_path_by_position(t_cmd *cmd_list, int position);

#endif