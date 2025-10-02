/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 23:09:31 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/02 02:13:07 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(void)
{
	int	fd;

	fd = open("test.txt" ,O_RDWR);
	if (fd < 0)
	{
		perror("Error fd < 0");
		return (1);
	}
	if (close(fd))
	{
		printf("%s\n", strerror(errno));
		printf("errno: %d\n", errno);
		return (1);
	}
	if (access("test.txt", F_OK | R_OK) == 0)
		printf("Existe e lido!\n");
	else
		printf("Não existe e não lido : <\n");
	printf("Passou :>");
	return (0);
}
