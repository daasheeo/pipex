/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:51:02 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/18 19:19:47 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Libft/libft.h"

static char	*ft_read_buffer(char *buffer, int fd)
{
	char	*buff;
	int		bytes_read;

	buff = malloc((1 + 1) * sizeof(char));
	if (!buff)
	{
		free(buffer);
		return (NULL);
	}
	bytes_read = 1;
	while (!ft_strchr((const char *)buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, 1);
		if (bytes_read == -1)
		{
			free(buff);
			free(buffer);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, buff);
	}
	free(buff);
	return (buffer);
}

static char	*ft_new_line(char *buffer)
{
	int		i;
	char	*new_line;

	i = 0;
	if (!buffer[i] || !buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	new_line = malloc(sizeof(char) * (i + 1 + (buffer[i] == '\n')));
	if (!new_line)
		return (free(buffer), NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		new_line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		new_line[i] = buffer[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

static char	*ft_clean_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*new_line;

	if (fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer[fd] = ft_read_buffer(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	new_line = ft_new_line(buffer[fd]);
	buffer[fd] = ft_clean_buffer(buffer[fd]);
	return (new_line);
}
