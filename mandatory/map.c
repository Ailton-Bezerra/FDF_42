/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:17:58 by ailbezer          #+#    #+#             */
/*   Updated: 2025/01/18 19:31:09 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	check_map(char *map)
{
	int		fd;
	char	*line;

	if (ft_strnstr(map, ".fdf", ft_strlen(map)) == NULL)
		exit_msg(2);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		exit_msg(3);
	line = get_next_line(fd);
	if (!line)
		exit_msg(4);
	free(line);
	get_next_line(-42);
	close(fd);
}
