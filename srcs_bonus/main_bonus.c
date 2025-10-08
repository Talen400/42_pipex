/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 23:09:31 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/08 05:42:15 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	ft_last(int argc, char **argv, char **env, int *fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_handler("fork error: ");
	if (!pid)
	{
		dup2(fds[1], 1);
		ft_exec(argv[argc - 2], env);
	}
	waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	int		fds[2];

	if (argc < 5)
		ft_handler("Usage: ./pipex infile cm1 cmd2 ... outfile");
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
			ft_handler("./pipex here_doc LIMIT cmd cmd1 ... outfile");
		i = 3;
		fds[1] = ft_open(argv[argc - 1], 2);
		ft_heredoc(argv);
	}
	else
	{
		i = 2;
		fds[0] = ft_open(argv[1], 0);
		fds[1] = ft_open(argv[argc - 1], 1);
		dup2(fds[0], 0);
	}
	while (i < argc - 2)
		ft_pipex(argv[i++], env);
	ft_last(argc, argv, env, fds);
	return (0);
}
