/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 23:09:31 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/09 03:42:10 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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

int	main(int argc, char **argv, char **env)
{
	int		i;
	int		in;

	if (argc < 5)
		ft_handler("Usage: ./pipex infile cm1 cmd2 ... outfile");
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
			ft_handler("Usage: ./pipex here_doc LIMIT cmd cmd1 ... outfile");
		i = 3;
		ft_heredoc(argv);
	}
	else
	{
		i = 2;
		in = ft_open(argv[1], 0);
		dup2(in, 0);
		close(in);
	}
	while (i < argc - 2)
		ft_pipex(argv[i++], env);
	ft_last(argc, argv, env);
	return (0);
}
