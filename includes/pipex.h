/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:50:00 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/07 18:21:14 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

// pipex
void	ft_pipex(char **argv, char **env);

// get path
char	*ft_path_cmd(char *cmd, char **env);

// pipex utils
int		ft_open(char *filename, int in_or_out);
void	ft_free_split(char **str);
void	ft_handler(const char *str);

#endif
