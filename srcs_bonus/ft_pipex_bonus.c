/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:13:34 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/09 21:08:45 by tlavared         ###   ########.fr       */
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
		ft_handler(path);
	}
}

void	ft_pipe(char *cmd, char **env)
{
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) == -1)
		ft_handler("pipe");
	pid = fork();
	if (pid == -1)
		ft_handler("fork");
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

static void	ft_last(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		out;

	out = ft_open(argv[argc - 1], 1);
	pid = fork();
	if (pid == -1)
		ft_handler("fork error");
	if (!pid)
	{
		dup2(out, 1);
		close(out);
		ft_exec(argv[argc - 2], env);
	}
	close(out);
	waitpid(pid, NULL, 0);
}

int	ft_pipex(int argc, char **argv, char **env)
{
	int	i;
	int	in;

	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
			ft_handler_logic("Usage: ./pipex here_doc LIMIT cmd cmd1 ... outfile");
		i = 3;
		ft_heredoc(argv);
	}
	else
	{
		if (access(argv[1], R_OK == -1))
			ft_handler(argv[1]);
		i = 2;
		in = ft_open(argv[1], 0);
		dup2(in, 0);
		close(in);
	}
	while (i < argc - 2)
		ft_pipe(argv[i++], env);
	ft_last(argc, argv, env);
	return (0);
}
