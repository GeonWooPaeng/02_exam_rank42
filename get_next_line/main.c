/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 12:57:30 by gpaeng            #+#    #+#             */
/*   Updated: 2021/01/14 13:52:20 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main()
{
    int		fd;		
    char	*line;
	int		ret;

	if ((fd = open("./test.txt", O_RDONLY)) == -1)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	while ((ret = get_next_line(&line)) > 0)
	{
		printf(">>> %d\n", ret);
		printf("line >> %s\n", line);
		free(line);
	}
	printf("line >> %s\n", line);
	free(line);

	return (0);
}

