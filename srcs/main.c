/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 23:09:31 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/08 05:42:35 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
	{
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
		return (1);
	}
	ft_pipex(argv, env);
	return (0);
}
