/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:00:36 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/24 17:39:16 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		print_map(t_map *map) // test
{
	int i;
	int j;

	i = -1;
	ft_putendl("--- MAP int ---");
	while (++i < map->y)
	{
		j = -1;
		while (++j < map->x)
			ft_putnbr(map->map[i][j]);
		ft_putchar('\n');
	}
	ft_putendl("---------------");
}

static void		print_point(t_pts **point, t_map *map) // test
{
	int i;
	int j;

	i = 0;
	ft_putendl("--- MAP pts ---");
	while (i < map->y)
	{
		j = 0;
		while (j < map->x)
		{
			ft_putendl("-----");
			printf("x = |%d|\ny = |%d|\nz = |%d|\n", point[i][j].x_pts, point[i][j].y_pts, point[i][j].z_pts);
			printf("X = |%f|\nY = |%f|\n", point[i][j].X, point[i][j].Y);
			j++;
		}
		i++;
	}
	ft_putendl("---------------");
}

static t_pts	get_coord(int map, int x, int y)
{
	t_pts	point;
	float	cst1;
	float	cst2;

	cst1 = 0.8; // entre 0.5 et 1
	cst2 = 0.8; // entre 0.5 et 1
	point.x_pts = x;
	point.y_pts = y;
	point.z_pts = map;
	point.X = (cst1 * point.x_pts) - (cst2 * point.y_pts); // projection iso
	point.Y = point.z_pts + ((cst1 / 2) * point.x_pts) + ((cst2 / 2) * point.y_pts); // projection iso
//	point.X *= -1;
	point.Y *= -1;
	//	point.X = point.x_pts + (cst1 * point.z_pts); // projection //
	//	point.Y = point.y_pts + ((cst1 / 2) * point.z_pts); // projection //
	return (point);
}

static t_pts	**convert_map(t_map *map, t_pts **point, t_env *env)
{
	int i;
	int j;
	int x_min;
	int y_min;
	int x_max;
	int	y_max;

	i = -1;
	x_min = 0;
	y_min = 0;
	x_max = 0;
	y_max = 0;
	map->x_range = 0;
	map->y_range = 0;
	while (++i < map->y)
	{
		j = -1;
		point[i] = (t_pts *)malloc(sizeof(t_pts) * (map->x));
		while (++j < map->x)
		{
			point[i][j] = get_coord(map->map[i][j], i, j);
			if (point[i][j].X > x_max)
				x_max = point[i][j].X;
			else if (point[i][j].X < x_min)
				x_min = point[i][j].X;
			if (point[i][j].Y > y_max)
				y_max = point[i][j].Y;
			else if (point[i][j].Y < y_min)
				y_min = point[i][j].Y;
		}
	}
	map->x_range = x_max - x_min;
	map->y_range = y_max - y_min;
	return (map->point);
}

static void		put_map(t_env *env, t_map *map)
{
	int		i;
	int		j;
	float	x_img;
	float	y_img;
	float	x_offset;
	float	y_offset;
	float	coef_x;
	float	coef_y;

	printf("map->x = |%d|\n", map->x);
	printf("map->y = |%d|\n", map->y);
	printf("x_range = |%f|\n", map->x_range);
	printf("y_range = |%f|\n", map->y_range);

	//coef_x = env->x_win / ((map->x_max - map->x_min));
	//coef_y = env->y_win / ((map->y_max - map->y_min));
	coef_x = env->x_win / (map->x_range * 1.2);
	coef_y = env->y_win / (map->y_range * 1.2);
	printf("coef_x = |%f|\n", coef_x);
	printf("coef_y = |%f|\n", coef_y);

	//x_img = (coef_x * (map->x_range)) / 2;
	//y_img = (coef_x * (map->y_range)) / 2;
	x_img = coef_x * map->x_range;
	y_img = coef_x * map->y_range;
	printf("x_img = |%f|\n", x_img);
	printf("y_img = |%f|\n", y_img);

	//x_offset = (env->x_win - x_img);
	x_offset = (env->x_win - map->x_range) / 2;
	y_offset = (env->y_win - map->y_range);
	printf("x_offset = |%f|\n", x_offset);
	printf("y_offset = |%f|\n", y_offset);

	i = -1;
	while (++i < map->y)
	{
		j = -1;
		while (++j < map->x)
			mlx_pixel_put(env->mlx, env->win, x_offset + (coef_x * map->point[i][j].X), y_offset + (coef_x * map->point[i][j].Y), 0x000FFFFF);
	}
}

static void		build_map(t_env *env, t_map *map)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, env->x_win, env->y_win, "| Fdf |");
	env->img = mlx_new_image(env->mlx, env->x_win, env->y_win);

	map->point = (t_pts **)malloc(sizeof(t_pts *) * (map->y));
	map->point = convert_map(map, map->point, env);

	print_point(map->point, map); // test

	put_map(env, map);

	mlx_loop(env->mlx);
}

int				main(int ac, char **av, char **environ)
{
	int 	x;
	int 	y;
	t_map	*map;
	t_env	*env;

	e_param(ac, environ);			// check if ac = 2 and if env exist
	env = init_env();				// init fd et malloc
	map = parsing(ac, av[1], env);	// parsing
	print_map(map);					// test
	build_map(env, map);
	return (0);
}
