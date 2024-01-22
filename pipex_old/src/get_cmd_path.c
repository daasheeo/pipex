/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:17:17 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/19 10:26:36 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libft/libft.h"
#include "../includes/pipex.h"

static char	**ft_get_splitted_path(char **envp)
{
	char	*path;
	char	**path_split;

	path = ft_getenv("PATH", envp);
	if (!path)
		ft_error("PATH not found");
	path_split = ft_split(path, ':');
	if (!path_split)
		ft_error("ft_split failed");
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
	while (path_split[i])
	{
		path_cmd = ft_strjoin(path_split[i], "/");
		temp = ft_strjoin(path_cmd, cmd);
		if (!path_cmd)
			ft_error("ft_strjoin failed");
		if (access(temp, F_OK) == 0)
			return (temp);
		i++;
	}
	i = -1;
	while (path_split[++i])
		free(path_split[i]);
	free(path_split);
	return (NULL);
}
