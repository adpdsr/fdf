/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:00:36 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/27 19:20:01 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			hook_key(int keycode, t_map *map)
{
	printf("key event = %d\n", keycode);
	if (keycode == 53 || keycode == 12)
	{
		ft_putendl("exit");
		exit(0);
	}
	if (keycode == 69 || keycode == 24)
	{
		map->zoom += 1;
		mlx_clear_window(map->mlx, map->win);
		put_map(map);
	}
	if (keycode == 78 || keycode == 27)
	{
		map->zoom -= 1;
		mlx_clear_window(map->mlx, map->win);
		put_map(map);
	}
	if (keycode == 123)
	{
		map->offset_x -= 10;
		map->offset_y -= 10;
		mlx_clear_window(map->mlx, map->win);
		put_map(map);
	}
	if (keycode == 124)
	{
		map->offset_x += 10;
		map->offset_y += 10;
		mlx_clear_window(map->mlx, map->win);
		put_map(map);
	}
	if (keycode == 126)
	{
		map->offset_x += 10;
		map->offset_y -= 10;
		mlx_clear_window(map->mlx, map->win);
		put_map(map);
	}
	if (keycode == 125)
	{
		map->offset_x -= 10;
		map->offset_y += 10;
		mlx_clear_window(map->mlx, map->win);
		put_map(map);
	}
	if (keycode == 116)
	{
		map->height += 1;
		mlx_clear_window(map->mlx, map->win);
		put_map(map);
	}
	if (keycode == 121)
	{
		map->height -= 1;
		mlx_clear_window(map->mlx, map->win);
		put_map(map);
	}
	if (keycode == 83) // a revoir
	{
		if (map->factor > 0.2)
		{
			map->factor -= 0.1;
			map->offset_x -= 100;
			map->offset_y += 100;
		}
		printf("factor = |%f|\n", map->factor);
		mlx_clear_window(map->mlx, map->win);
		put_map(map);
	}
	if (keycode == 84) // a revoir
	{
		if (map->factor < 0.8)
		{
			map->factor += 0.1;
			map->offset_x += 100;
			map->offset_y -= 100;
		}
		printf("factor = |%f|\n", map->factor);
		mlx_clear_window(map->mlx, map->win);
		put_map(map);
	}
	return (0);
}

void		do_map(t_env *env, t_map *map)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, env->x_win, env->y_win, "| Fdf |");
	map->mlx = env->mlx;
	map->win = env->win;
	env->img = mlx_new_image(env->mlx, env->x_win, env->y_win);
	put_map(map);
	mlx_key_hook(env->win, &hook_key, map);
	mlx_loop(env->mlx);
}

static void    e_param(int ac, char **env)
{
	if (ac != 2 || !env || !(*env))
	{
		if (ac != 2)
			ft_putendl_fd("usage: ./fdf file1", 2);
		if (!env || !(*env))
			ft_putendl_fd("fdf cant be launch with empty env", 2);
		exit(1);
	}
}

static t_env   *init_env(char *av)
{
	t_env   *env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		exit(1);
	if ((env->fd = open(av, O_RDONLY)) == -1)
		exit(1);
	env->y_win = 800;
	env->x_win = 1200;
	return (env);
}

int				main(int ac, char **av, char **environ)
{
	int 	x;
	int 	y;
	t_map	*map;
	t_env	*env;

	e_param(ac, environ);
	env = init_env(av[1]);
	map = parsing(av[1], env);
//	env->mlx = mlx_init();
//	env->win = mlx_new_window(env->mlx, env->x_win, env->y_win, "| Fdf |");
	do_map(env, map);
//	mlx_loop(env->mlx);
	return (0);
}
