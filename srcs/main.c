/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 23:09:31 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/02 18:14:36 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(void)
{
	int	fd;
	int	fd_cp;

	fd = open("test.txt" ,O_RDWR);
	if (fd < 0)
	{
		perror("Error fd < 0");
		return (1);
	}
	fd_cp = dup(fd);
	printf("fd value: %d\n", fd);
	if (close(fd))
	{
		printf("%s\n", strerror(errno));
		printf("errno: %d\n", errno);
		return (1);
	}
	printf("Lida do fd_cp: %s\n", get_next_line(fd_cp));
	printf("fd_cp value: %d\n", fd_cp);
	if (close(fd_cp))
		perror("Error fd_cp");
	printf("Passou :>\n");
	return (0);
}
