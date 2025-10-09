/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:13:34 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/09 04:05:15 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_exec(char *cmd, char **env)
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

void	ft_pipex(char *cmd, char **env)
{
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) == -1)
		ft_handler("error pipe");
	pid = fork();
	if (pid == -1)
		ft_handler("error fork");
	if (!pid)
	{
		dup2(fds[1], 1);
		close(fds[0]);
		close(fds[1]);
		ft_exec(cmd, env);
	}
	else
	{
		dup2(fds[0], 0);
		close(fds[0]);
		close(fds[1]);
		waitpid(pid, NULL, 0);
	}
}
