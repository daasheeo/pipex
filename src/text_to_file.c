/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_to_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:13:39 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/15 12:32:20 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libft/libft.h"
#include "../includes/pipex.h"

void	ft_text_to_file(char *delimiter, int fd)
{
	char	*line;

	line = NULL;
	fprintf(stderr, "delimiter: %s\n", delimiter);
	fprintf(stderr, "fd: %d\n", fd);
	fprintf(stderr, "STDIN_FILENO: %d\n", STDIN_FILENO);
	fprintf(stderr, "STDOUT_FILENO: %d\n", STDOUT_FILENO);
	fprintf(stderr, "STDERR_FILENO: %d\n", STDERR_FILENO);
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
