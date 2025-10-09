#include "includes/pipex.h"

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

int	main(int argc, char **argv, char **env)
{
	int	i;

	/*
	i = 0;
	printf("argv: \n");
	while (argv[i] != NULL)
	{
		printf("argv[%d]: %s\n", i, argv[i]);
		i++;
	}
	*/
	if (argc < 2)
		return (0);
	printf("pegando meu env '%s': %s\n", argv[1],
			ft_getenv(argv[1], env));
	if (argc != 3)
		return (0);
	char	*exec;
	exec = ft_path_cmd(argv[2], env);
	printf("Meu cmd '%s' encontrado! : %s\n", argv[2], exec);
	
	i = 0;
	printf("env antes do execve: \n");
	while (env[i] != NULL)
	{
		printf("env[%d]: %s\n", i, env[i]);
		i++;
	}

	if (exec)
		free(exec);
	ft_exec(argv[2], env);
	
	i = 0;
	printf("env antes do execve: \n");
	while (env[i] != NULL)
	{
		printf("env[%d]: %s\n", i, env[i]);
		i++;
	}
	(void ) i;
	(void ) argc;
}
