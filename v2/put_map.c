/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:00:36 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/26 18:22:05 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		draw_seg(t_env *env, t_map *map)
{
	double	factor;

	factor = 0.0;
	map->seg.dx = (map->seg.x2 - map->seg.x1);
	map->seg.dy = (map->seg.y2 - map->seg.y1);
	while (factor <= 1)
	{
		env->x = map->seg.x1 + map->seg.dx * factor;
		env->y = map->seg.y1 + map->seg.dy * factor;
		mlx_pixel_put(env->mlx, env->win, env->x, env->y, BASE_COLOR);
		factor += 1.0 / sqrt((map->seg.dx * map->seg.dx) + (map->seg.dy * map->seg.dy));
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
	map->seg.y1 = (y1 * 0.5) - (0.5 * (x1 + map->seg.z1));
	map->seg.y2 = (y2 * 0.5) - (0.5 * (x2 + map->seg.z2));
}

static void		draw_line_v(t_env *env, t_map *map, int i, int j)
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
	draw_seg(env, map);
}

static void		draw_line_h(t_env *env, t_map *map, int i, int j)
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
	draw_seg(env, map);
}

static void		print_map(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->h)
	{
		while (j < map->l)
		{
			ft_putnbr(map->map[i][j]);
			ft_putchar('|');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

void			put_map(t_env *env, t_map *map)
{
	int i;
	int j;

	i = 0;
//	print_map(map); // test
	while (i < map->h -1)
	{
		ft_putendl("test1");
		j = 0;
		while (j < map->l -1)
		{
			draw_line_v(env, map, i, j);
			draw_line_h(env, map, i, j);
			j++;
		}
		i++;
	}
}
