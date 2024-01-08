/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:08:02 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/08 16:09:25 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_get_infile_fd(t_pipex *pipex)
{
	int	f1;

	f1 = open(pipex->infile, O_RDONLY);
	if (f1 < 0)
		ft_error("open failed");
	pipex->in_fd = f1;
}

void	ft_get_outfile_fd(t_pipex *pipex)
{
	int f1;

	f1 = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (f1 < 0)
		ft_error("open failed");
	pipex->out_fd = f1;
}