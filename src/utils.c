/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:33:25 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/22 11:38:00 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/Libft/libft.h"

void ft_free_cmd(char **cmd_args)
{
    int i;
    
    i = 0;
    while (cmd_args[i])
    {
        free(cmd_args[i]);
        i++;
    }
    free(cmd_args);
}

void ft_exit_error(int option)
{
    if (option == 1)
        ft_putstr_fd("Error: Wrong number of arguments\n", 2);       
    exit(0);
}
