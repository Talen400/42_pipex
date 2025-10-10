/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 01:05:07 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/10 01:05:39 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static size_t	ft_count_words(const char *s, char d, char literal)
{
	size_t	count;
	int		in_word;
	int		in_literal;

	count = 0;
	in_word = 0;
	in_literal = 0;
	while (*s)
	{
		if (*s == literal)
			in_literal = !in_literal;
		else if (*s != d || in_literal)
		{
			if (!in_word && ++count)
				in_word = 1;
		}
		else
			in_word = 0;
		s++;
	}
	return (count);
}

static char	**ft_null(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i]);
	free(str);
	return (NULL);
}

static char	*ft_extract(const char **s, char d, char literal)
{
	const char	*start;
	size_t		len;
	int			in_literal;

	in_literal = 0;
	len = 0;
	while (**s == d)
		(*s)++;
	if (**s == literal)
	{
		in_literal = 1;
		(*s)++;
	}
	start = *s;
	while (**s && !(!in_literal && **s == d) && !(in_literal && **s == literal))
	{
		len++;
		(*s)++;
	}
	if (in_literal && **s == literal)
		(*s)++;
	return (ft_substr(start, 0, len));
}

char	**ft_split_lit(const char *s, char d, char literal)
{
	size_t	i;
	size_t	len;
	char	**str;

	len = ft_count_words(s, d, literal);
	str = malloc ((len + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	while (*s && i < len)
	{
		while (*s == d)
			s++;
		if (*s == '\0')
			break ;
		str[i] = ft_extract((const char **) &s, d, literal);
		if (!str[i])
			return (ft_null(str));
		i++;
	}
	str[i] = NULL;
	return (str);
}
