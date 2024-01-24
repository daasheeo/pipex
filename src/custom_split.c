/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:58:39 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/23 11:11:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../libs/Libft/libft.h"

static void	free_lst_memory(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static size_t	ft_big_array_size(char *string, char splitter, char flag)
{
	int	i;
	int	n_words;
	int	trigger;
	int	flag_trigger;

	i = 0;
	n_words = 0;
	trigger = 0;
	flag_trigger = 0;
	while (string[i])
	{
		if (string[i] == flag)
			flag_trigger = !flag_trigger;
		if (string[i] == splitter && !flag_trigger)
			trigger = 0;
		else if (!trigger && !flag_trigger)
		{
			trigger = 1;
			n_words++;
		}
		i++;
	}
	return (n_words);
}

static char	*ft_word_dup(const char *s1, int start, int finish)
{
	char	*res_word;
	int		i;

	i = 0;
	res_word = malloc((finish - start + 1) * sizeof(char));
	if (!res_word)
		return (NULL);
	while (start < finish)
		res_word[i++] = s1[start++];
	res_word[i] = '\0';
	return (res_word);
}

char	**ft_custom_split(char *string, char splitter, char flag)
{
	char **split;
	size_t i;
	size_t j;
	int trigger;
	int flag_count;
	split = malloc((ft_big_array_size(string, splitter, flag) + 1)
			* sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	trigger = -1;
	flag_count = 0;
	while (i <= ft_strlen(string))
	{
		if (string[i] == flag)
			flag_count++;
		if (string[i] != splitter && trigger == -1)
			trigger = i;
		else if ((string[i] == splitter || string[i] == '\0'
				|| i == ft_strlen(string)) && flag_count % 2 == 0
			&& trigger >= 0)
		{
			split[j++] = ft_strtrim(ft_word_dup(string, trigger, i), "\'");
			if (!split[j - 1])
				return (free_lst_memory(split), NULL);
			trigger = -1;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}
