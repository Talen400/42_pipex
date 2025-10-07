/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 23:09:31 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/07 18:04:19 by tlavared         ###   ########.fr       */
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
	if (fd < 0)
		ft_handler("open: ");
	return (fd);
}

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		printf("sub sendo capturado: %s\n", sub);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		i++;
		free(sub);
	}
	return (env[i]);
}

char	*ft_path_cmd(char *cmd, char **env)
{
	int		i;
	char	*path_part;
	char	*exec;
	char	**path;
	char	**s_cmd;

	path = ft_split(ft_getenv("PATH", env), ':');
	i = -1;
	s_cmd = ft_split(cmd, ' ');
	while (path[++i])
	{
		path_part = ft_strjoin(path[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_split(s_cmd);
			ft_free_split(path);
			return (exec);
		}
		free(exec);
	}
	ft_free_split(path);
	ft_free_split(s_cmd);
	return (ft_strdup(""));
}

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
		perror("exec child: ");
		exit(1);
	}
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
	close(fds[1]);
	ft_exec(argv[3], env);
}

void	ft_pipex(char **argv, char **env)
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
	printf("filho 1 terminou!\n");
	waitpid(pid2, NULL, 0);
	printf("filho 2 terminou!\n");
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
	{
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
		return (1);
	}
	ft_pipex(argv, env);
	(void ) argc;
	return (0);
}
