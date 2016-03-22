/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:00:36 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/22 17:33:05 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		print_map(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->y)
	{
		j = 0;
		while (j < map->x)
		{
			ft_putnbr(map->map[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
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

	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, 1200, 800, "| Fdf |");
	env->img = mlx_new_image(env->mlx, env->x_win, env->y_win);

	y = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			mlx_pixel_put(env->mlx, env->win, x, y, 0x000FFFFF);
			x++;
		}
		y++;
	}
	mlx_loop(env->mlx);
	return (0);
}
