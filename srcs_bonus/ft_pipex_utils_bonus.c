/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:13:10 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/10 01:30:42 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_handler(const char *str, int exit_code)
{
	perror(str);
	exit(exit_code);
}

void	ft_handler_logic(const char *str, int exit_code)
{
	ft_putstr_fd((char *) str, 2);
	exit(exit_code);
}

void	ft_free_split(char **str)
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

int	ft_open(char *filename, int in_or_out)
{
	int	fd;

	fd = -1;
	if (in_or_out == 0)
		fd = open(filename, O_RDONLY, 0777);
	else if (in_or_out == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (in_or_out == 2)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
		ft_handler(filename, 1);
	return (fd);
}
