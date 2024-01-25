/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesmunoz <jesmunoz@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:58:39 by jesmunoz          #+#    #+#             */
/*   Updated: 2024/01/25 14:06:09 by jesmunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../libs/Libft/libft.h"

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

void	ft_increment_flag_and_trigger(int *flag_count, int *trigger,
		char *string, int i)
{
	char	*c;

	c = NULL;
	if (string[i] == '\'' || string[i] == '\"' || (string[i] == '\'' && string[i
		+ 1] == '\"'))
	{
		if (c == NULL)
			c = string[i];
		if (c == string[i])
			(*flag_count)++;
		fprintf(stderr, "flag_count: %d\n", *flag_count);
	}
	if ((string[i] != '\'' || string[i] == '\"' || (string[i] == '\''
			&& string[i + 1] == '\"')) && *trigger == -1)
	{
		*trigger = i;
		fprintf(stderr, "trigger: %d\n", *trigger);
	}
}

static int	ft_process_string(char *string, char **split, char splitter,
		char flag)
{
	size_t	i;
	size_t	j;
	int		trigger;
	int		flag_count;

	i = -1;
	j = 0;
	trigger = -1;
	flag_count = 0;
	(void)flag;
	while (++i <= ft_strlen(string))
	{
		ft_increment_flag_and_trigger(&flag_count, &trigger, string, i);
		if ((string[i] == splitter || string[i] == '\0'
				|| i == ft_strlen(string)) && flag_count % 2 == 0
			&& trigger >= 0)
		{
			ft_putstr_fd(ft_strtrim(ft_word_dup(string, trigger, i), "\'\""), 2);
			ft_putstr_fd("\n", 2);
			split[j++] = ft_strtrim(ft_word_dup(string, trigger, i), "\'\"");
			if (!split[j - 1])
				return (free_lst_memory(split), 0);
			trigger = -1;
		}
	}
	return (split[j] = NULL, 1);
}

char	**ft_custom_split(char *string, char splitter, char flag)
{
	char	**split;

	split = malloc((ft_big_array_size(string, splitter, flag) + 1)
		* sizeof(char *));
	if (!split)
		return (NULL);
	if (!ft_process_string(string, split, splitter, flag))
		return (NULL);
	return (split);
}
