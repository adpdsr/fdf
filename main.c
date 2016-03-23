/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:00:36 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/23 18:57:15 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		print_map(t_map *map)
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

static void		print_point(t_pts **point, t_map *map)
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
			ft_putstr("x = ");
			ft_putnbr(point[i][j].x_pts);
			ft_putchar('\n');
			ft_putstr("y = ");
			ft_putnbr(point[i][j].y_pts);
			ft_putchar('\n');
			ft_putstr("z = ");
			ft_putnbr(point[i][j].z_pts);
			ft_putchar('\n');
			ft_putstr("X = ");
			ft_putnbr(point[i][j].X);
			ft_putchar('\n');
			ft_putstr("Y = ");
			ft_putnbr(point[i][j].Y);
			ft_putchar('\n');
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

	cst1 = 0.5; // entre 0.5 et 1
	cst2 = 0.5; // entre 0.5 et 1
	point.x_pts = x;
	point.y_pts = y;
	point.z_pts = map;
	point.X = (cst1 * point.x_pts) - (cst2 * point.y_pts); // projection iso
	point.Y = point.z_pts + ((cst1 / 2) * point.x_pts) + ((cst2 / 2) * point.y_pts); // projection iso
//	point.X = point.x_pts + (cst1 * point.z_pts); // projection //
//	point.Y = point.y_pts + ((cst1 / 2) * point.z_pts); // projection //
	return (point);
}

static t_pts	**convert_map(t_map *map, t_pts **point, t_env *env)
{
	int i;
	int j;

	i = 0;
	while (i < map->y)
	{
		j = 0;
		point[i] = (t_pts *)malloc(sizeof(t_pts) * (map->x));
		while (j < map->x)
		{
			//ft_putendl("test1");
			point[i][j] = get_coord(map->map[i][j], i, j);
			//ft_putendl("test2");
			mlx_pixel_put(env->mlx, env->win, 400 + (10 * point[i][j].X), 400 + (10 * point[i][j].Y), 0x000FFFFF); // test
			//ft_putendl("test3");
			j++;
		}
		i++;
	}	
	return (map->point);
}

static void		build_map(t_env *env, t_map *map)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, env->x_win, env->y_win, "| Fdf |");
	env->img = mlx_new_image(env->mlx, env->x_win, env->y_win);

	map->point = (t_pts **)malloc(sizeof(t_pts *) * (map->y));
	map->point = convert_map(map, map->point, env);

	print_point(map->point, map); // test
	
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
