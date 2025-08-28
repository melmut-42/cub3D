/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunajed <mmunajed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:42:06 by mmunajed          #+#    #+#             */
/*   Updated: 2024/10/18 17:08:06 by mmunajed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c);
static char	*extract_word(const char *s, int start_i, int end_i);
static void	*free_memory(char **words_arr, int allocated_count);
static void	init_vars(size_t *curr_i, int *word_i, int *start_word_i);

char	**ft_split(char const *s, char c)
{
	char	**words_arr;
	int		start_word_i;
	int		word_i;
	size_t	curr_i;

	init_vars(&curr_i, &word_i, &start_word_i);
	words_arr = ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (!words_arr)
		return (NULL);
	while (curr_i <= ft_strlen(s))
	{
		if (s[curr_i] != c && start_word_i < 0)
			start_word_i = curr_i;
		else if ((s[curr_i] == c
				|| curr_i == ft_strlen(s)) && start_word_i >= 0)
		{
			words_arr[word_i] = extract_word(s, start_word_i, curr_i);
			if (!(words_arr[word_i]))
				return (free_memory(words_arr, word_i));
			start_word_i = -1;
			word_i++;
		}
		curr_i++;
	}
	return (words_arr);
}

static void	init_vars(size_t *curr_i, int *word_i, int *start_word_i)
{
	*curr_i = 0;
	*word_i = 0;
	*start_word_i = -1;
}

static void	*free_memory(char **words_arr, int allocated_count)
{
	int	i;

	i = 0;
	while (i < allocated_count)
	{
		free(words_arr[i]);
		i++;
	}
	free(words_arr);
	return (NULL);
}

static char	*extract_word(const char *s, int start_i, int end_i)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end_i - start_i + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start_i < end_i)
	{
		word[i] = s[start_i];
		i++;
		start_i++;
	}
	word[i] = 0;
	return (word);
}

static int	count_words(const char *s, char c)
{
	int	word_count;
	int	is_word;

	word_count = 0;
	is_word = 0;
	while (*s)
	{
		if (*s != c && is_word == 0)
		{
			is_word = 1;
			word_count++;
		}
		else if (*s == c)
			is_word = 0;
		s++;
	}
	return (word_count);
}
