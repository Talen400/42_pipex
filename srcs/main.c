/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 23:09:31 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/10 01:41:13 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
		ft_handler_logic("Usage: ./pipex infile cmd cmd outfile\n", 1);
	if (access(argv[1], R_OK) == -1)
	{
		ft_handler(argv[1], 1);
		return (1);
	}
	ft_pipex(argv, env);
	return (0);
}
