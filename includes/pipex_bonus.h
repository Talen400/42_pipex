/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:50:00 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/09 21:11:24 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

// pipex
int		ft_pipex(int argc, char **argv, char **env);

// get path
char	*ft_path_cmd(char *cmd, char **env);

// pipex utils
int		ft_open(char *filename, int in_or_out);
void	ft_free_split(char **str);
void	ft_handler(const char *str);
void	ft_handler_logic(const char *str);

// exec
void	ft_exec(char *cmd, char **env);

// heredoc
void	ft_heredoc(char	**argv);
#endif
