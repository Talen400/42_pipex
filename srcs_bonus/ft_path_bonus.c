/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:17:47 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/07 18:31:13 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static char	*ft_getenv(char *name, char **env)
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
