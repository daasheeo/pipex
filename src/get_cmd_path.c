/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:17:17 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/04 18:10:47 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libft/libft.h"
#include "../includes/pipex.h"

char	*ft_search_path(char *cmd, char **envp)
{
	char	*path;
	char	**path_split;
	char	*path_cmd;
	int		i;

	i = 0;
	path = ft_getenv("PATH", envp);
	if (!path)
		ft_error("PATH not found");
	path_split = ft_split(path, ':');
	if (!path_split)
		ft_error("ft_split failed");
	while (path_split[i])
	{
		path_cmd = ft_strjoin(path_split[i], "/");
		if (!path_cmd)
			ft_error("ft_strjoin failed");
		path_cmd = ft_strjoin(path_cmd, cmd);
		if (!path_cmd)
			ft_error("ft_strjoin failed");
		if (access(path_cmd, F_OK) == 0)
			return (path_cmd);
		i++;
	}
	return (NULL);
}

char	*ft_get_path_by_position(t_cmd *cmd_list, int position)
{
	t_cmd	*current_cmd;
	int		i;

	i = 0;
	current_cmd = cmd_list;
	while (current_cmd)
	{
		if (i == position)
			return (current_cmd->path);
		current_cmd = current_cmd->next;
		i++;
	}
	return (NULL);
}
