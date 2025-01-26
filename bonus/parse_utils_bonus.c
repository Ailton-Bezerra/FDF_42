/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 09:41:39 by ailbezer          #+#    #+#             */
/*   Updated: 2025/01/26 16:41:05 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	center_map(t_map *map)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < (unsigned int)map->height)
	{
		x = 0;
		while (x < (unsigned int)map->width)
		{
			map->matrix[y][x].x -= map->width / 2;
			map->matrix[y][x].y -= map->height / 2;
			x++;
		}
		y++;
	}
}

static int	process_line(t_map *map, char **div_line, int i)
{
	int		j;
	char	*color;

	j = 0;
	while (j < map->width)
	{
		map->matrix[i][j].x = (float)j;
		map->matrix[i][j].y = (float)i;
		map->matrix[i][j].z = (float)(ft_atoi(div_line[j]));
		if (map->matrix[i][j].z > map->z_top)
			map->z_top = map->matrix[i][j].z;
		color = ft_strchr(div_line[j], ',');
		if (color)
			map->matrix[i][j].color = put_alpha(ft_hex_to_int(color + 1));
		else
		{
			if (map->matrix[i][j].z <= 0)
				map->matrix[i][j].color = put_alpha(0x0000FF);
			else
				map->matrix[i][j].color = put_alpha(0xFF0000);
		}
		j++;
	}
	return (0);
}

static int	process_map_line(t_map *map, char *line, int line_i)
{
	char	**div_line;

	div_line = ft_split(line, ' ');
	if (!div_line)
		exit_msg(5);
	process_line(map, div_line, line_i);
	free_split(div_line);
	return (1);
}

void	convert_map(t_map *map, char *map_id)
{
	int		line_i;
	int		fd;
	char	*line;

	fd = open(map_id, O_RDONLY);
	if (fd < 0)
		exit_msg(1);
	line_i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!process_map_line(map, line, line_i))
		{
			free(line);
			break ;
		}
		free(line);
		line_i++;
	}
	close(fd);
}
