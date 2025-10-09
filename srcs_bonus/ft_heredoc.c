/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 04:56:37 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/09 03:41:33 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_heredoc_put(char **argv, int *fds)
{
	char	*line;

	close(fds[0]);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0
			&& line[ft_strlen(argv[2])] == '\n')
		{
			free(line);
			close(fds[1]);
			exit(0);
		}
		ft_putstr_fd(line, fds[1]);
		free(line);
	}
}

void	ft_heredoc(char	**argv)
{
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) == -1)
		ft_handler("heredoc pipe error");
	pid = fork();
	if (pid == -1)
		ft_handler("heredoc fork error");
	if (!pid)
		ft_heredoc_put(argv, fds);
	else
	{
		dup2(fds[0], 0);
		close(fds[0]);
		close(fds[1]);
		wait(NULL);
	}
}
