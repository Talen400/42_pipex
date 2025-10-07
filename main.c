/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 23:09:31 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/07 02:05:20 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_handler(const char *str)
{
	perror(str);
	exit(-1);
}

void	ft_free_split(char **str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int		ft_open(char *filename, int in_or_out)
{
	int	fd;

	fd = -1;
	if (in_or_out == 0)
		fd = open(filename, O_RDONLY, 0777);
	else if (in_or_out == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (fd < 0)
		ft_handler("open: ");
	return (fd);
}


void	ft_exec(char *cmd, char **env)
{
	char	**s_cmd;

	s_cmd = ft_split(cmd, ' ');

}

void	ft_child_in(char **argv, int *fds, char **env)
{
	int	fd;

	fd = ft_open(argv[1], 0);
	dup2(fd, 0);
	dup2(fds[1], 1);
	close(fds[0]);
	ft_exec(argv[2], env);
}

void	ft_child_out(char **argv, int *fds, char **env)
{
	int	fd;

	fd = ft_open(argv[4], 1);
	dup2(fd, 1);
	dup2(fds[0], 0);
	close(fds[0]);
	ft_exec(argv[3], env);
}

void	ft_pipex(int argc, char **argv, char **env)
{
	int		fds[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fds) == -1)
		ft_handler("pipe: ");
	pid1 = fork();
	if (pid1 == -1)
		ft_handler("fork: ");
	if (!pid1)
		ft_child_in(argv, fds, env);
	pid2 = fork();
	if (pid2 == -1)
		ft_handler("fork: ");
	if (!pid2)
		ft_child_out(argv, fds, env);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
	{
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
		return (1);
	}
	ft_pipex(argc, argv, env);
	return (0);
}
