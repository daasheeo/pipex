/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:17:17 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/29 17:27:04 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/Libft/libft.h"
#include "../include/pipex.h"

static char	**ft_get_splitted_path(char **envp)
{
	char	**path_split;

	path_split = ft_split(ft_getenv("PATH", envp), ':');
	if (!path_split)
	{
		free_lst_memory(path_split);
		ft_exit_error(127, ERR_ENV, NULL);
	}
	return (path_split);
}

char	*ft_search_path(char *cmd, char **envp)
{
	char	**path_split;
	char	*path_cmd;
	char	*temp;
	int		i;

	path_split = ft_get_splitted_path(envp);
	i = 0;
	while (path_split[++i])
	{
		path_cmd = ft_strjoin(path_split[i], "/");
		temp = ft_strjoin(path_cmd, cmd);
		free(path_cmd);
		if (access(temp, F_OK | X_OK) == 0)
			return (temp);
		free(temp);
	}
	i = -1;
	while (path_split[++i])
		free(path_split[i]);
	free(path_split);
	return (NULL);
}
