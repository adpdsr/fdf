/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:00:36 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/11/07 16:50:36 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void		draw_seg(t_map *map, int i, int j)
{
	double	x;
	double	y;

	i = 0;
	j = 0;
	x = map->seg.x1;
	map->seg.dx = map->seg.x2 - map->seg.x1;
	map->seg.dy = map->seg.y2 - map->seg.y1;
	while (x < map->seg.x2)
	{
		y = map->seg.y1 + map->seg.dy * (x - map->seg.x1) / map->seg.dx;
		mlx_pixel_put(map->mlx, map->win, x, y, get_color(map));
		x += 0.2;
	}
}

static void		convert_iso(t_map *map)
{
	double x1;
	double x2;
	double y1;
	double y2;

	x1 = map->seg.x1;
	y1 = map->seg.y1;
	x2 = map->seg.x2;
	y2 = map->seg.y2;
	map->seg.x1 = x1 + y1;
	map->seg.x2 = x2 + y2;
	if (!map->seg.z1)
		map->color = BASE_COLOR;
	else if (map->seg.z1)
		map->color = RED;
	map->seg.y1 = (y1 * map->factor) - (map->factor * (x1 + map->seg.z1));
	map->seg.y2 = (y2 * map->factor) - (map->factor * (x2 + map->seg.z2));
}

static void		draw_line_v(t_map *map, int i, int j)
{
	double x1;
	double x2;
	double y1;
	double y2;

	y1 = map->offset_y;
	y2 = map->offset_y;
	x1 = map->offset_x + i * map->zoom;
	x2 = map->offset_x + (i + 1) * map->zoom;
	map->seg.x1 = x1;
	map->seg.y1 = y1 + j * map->zoom;
	map->seg.z1 = map->height * map->map[i][j];
	map->seg.x2 = x2;
	map->seg.y2 = y2 + j * map->zoom;
	map->seg.z2 = map->height * map->map[i + 1][j];
	convert_iso(map);
	draw_seg(map, i, j);
}

static void		draw_line_h(t_map *map, int i, int j)
{
	double x1;
	double x2;
	double y1;
	double y2;

	x1 = map->offset_x;
	x2 = map->offset_x;
	y1 = map->offset_y + j * map->zoom;
	y2 = map->offset_y + (j + 1) * map->zoom;
	map->seg.x1 = x1 + i * map->zoom;
	map->seg.y1 = y1;
	map->seg.z1 = map->height * map->map[i][j];
	map->seg.x2 = x1 + i * map->zoom;
	map->seg.y2 = y2;
	map->seg.z2 = map->height * map->map[i][j + 1];
	convert_iso(map);
	draw_seg(map, i, j);
}

void			put_map(t_map *map)
{
	int i;
	int j;

	i = -1;
	while (++i < map->h)
	{
		j = -1;
		while (++j < map->l)
		{
			if (i < (map->h - 1))
				draw_line_v(map, i, j);
			if (j < (map->l - 1))
				draw_line_h(map, i, j);
		}
	}
}
