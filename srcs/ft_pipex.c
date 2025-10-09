/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:13:34 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/09 03:40:57 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	ft_exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	path = ft_path_cmd(cmd, env);
	s_cmd = ft_split(cmd, ' ');
	if (execve(path, s_cmd, env) == -1)
	{
		ft_free_split(s_cmd);
		free(path);
		perror("exec child");
		exit(1);
	}
}

static void	ft_child_in(char **argv, int *fds, char **env)
{
	int	fd;

	fd = ft_open(argv[1], 0);
	dup2(fd, 0);
	dup2(fds[1], 1);
	close(fd);
	close(fds[0]);
	close(fds[1]);
	ft_exec(argv[2], env);
}

static void	ft_child_out(char **argv, int *fds, char **env)
{
	int	fd;

	fd = ft_open(argv[4], 1);
	dup2(fd, 1);
	dup2(fds[0], 0);
	close(fd);
	close(fds[0]);
	close(fds[1]);
	ft_exec(argv[3], env);
}

void	ft_pipex(char **argv, char **env)
{
	int		fds[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fds) == -1)
		ft_handler("pipe");
	pid1 = fork();
	if (pid1 == -1)
		ft_handler("fork");
	if (!pid1)
		ft_child_in(argv, fds, env);
	pid2 = fork();
	if (pid2 == -1)
		ft_handler("fork");
	if (!pid2)
		ft_child_out(argv, fds, env);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
