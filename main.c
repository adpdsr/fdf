/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:00:36 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/25 12:33:51 by adu-pelo         ###   ########.fr       */
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

static void		draw_line_h(t_env *env, t_map *map, int i, int j)
{
	float	x1;
	float	y1;
	float	x2;
	float	y2;
	float	coef_dir;
	float	move_x;
	float	move_y;	

	x1 = map->point[i][j].X;
	y1 = map->point[i][j].Y;
	x2 = map->point[i][j + 1].X;
	y2 = map->point[i][j + 1].Y;
	coef_dir = (y2 - y1) / (x2 - x1);
	printf("x1 = |%f|\ny1 = |%f|\n", x1, y1);
	printf("x2 = |%f|\ny2 = |%f|\n", x2, y2);
	printf("coeff dir = |%f|\n", coef_dir);
	while (y1 != y2)
	{
		//ft_putendl("moving down");
		move_y = (y1 > y2) ? -1 : 1;
		while (x1 != x2)
		{
			if (x1 !== x2)
				break;
			printf("moving right : x1 = |%f|\nx2 = |%f|\nmove = |%f|\n", x1, x2, move_x);
			move_x = (x1 > x2) ? -0.1 : 0.1;
			mlx_pixel_put(env->mlx, env->win, map->x_offset + (map->coef * map->point[i][j].X), map->y_offset + (map->coef * map->point[i][j].Y), 0x000FFFFF);
			x1 += move_x;
		}
		y1 += move_y;
	}
}

static void		put_map(t_env *env, t_map *map)
{
	int		i;
	int		j;
	float	x_img;
	float	y_img;
	float	coef_x;
	float	coef_y;

	printf("map->x = |%d|\n", map->x);
	printf("map->y = |%d|\n", map->y);
	printf("x_range = |%f|\n", map->x_range);
	printf("y_range = |%f|\n", map->y_range);

	//coef_x = env->x_win / (map->x * 4);
	coef_x = env->x_win / (map->x_range * 2);
	coef_y = env->x_win / (map->y_range * 2);
	map->coef = (coef_x < coef_y) ? coef_x : coef_y;
	//coef_x = env->x_win / (map->x_range * 1.2);
	//coef_y = env->y_win / (map->y * 4);
	printf("coef_x = |%f|\n", coef_x);
	printf("coef_y = |%f|\n", coef_y);

	//x_img = (coef_x * (map->x_range)) / 2;
	//y_img = (coef_x * (map->y_range)) / 2;
	x_img = coef_x * map->x_range;
	y_img = coef_x * map->y_range;
	printf("x_img = |%f|\n", x_img);
	printf("y_img = |%f|\n", y_img);

	//x_offset = (env->x_win - x_img);
	map->x_offset = env->x_win / 2;
	map->y_offset = (map->y_range * coef_y);
	printf("x_offset = |%f|\n", map->x_offset);
	printf("y_offset = |%f|\n", map->y_offset);

	i = -1;
	while (++i < map->y)
	{
		j = -1;
		while (++j < map->x)
		{
			draw_line_h(env, map, i, j);
		//	if (point[x][y + 1])
		//	{
		//		draw_line_h(env, map, x, y);
		//	}
		//	if (point[x + 1][y])
		//	{
		//		draw_line_v(point[x][y], point[x + 1][y]);
		//	}
		}
	}
}

static void		do_map(t_env *env, t_map *map)
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
	env = init_env(av[1]);			// init fd et malloc
	map = parsing(av[1], env);		// parsing
	print_map(map);					// test
	do_map(env, map);
	return (0);
}
