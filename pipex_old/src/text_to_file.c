/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_to_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:13:39 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/18 19:23:55 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libft/libft.h"
#include "../includes/pipex.h"

void	ft_text_to_file(char *delimiter, int fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			ft_error("Error: heredoc delimiter not found");
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
}
