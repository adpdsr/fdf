/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:00:36 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/26 17:32:27 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		hook_key(int keycode, t_map *map, t_env *env)
{

	printf("key event = %d\n", keycode);
	if (keycode == 53 || keycode == 12)
	{
		ft_putendl("exit");
		exit(0);
	}
	if (keycode == 69 || keycode == 24)
	{
		ft_putendl("zoom in");
		map->zoom += 1;
	}
	if (keycode == 78 || keycode == 27)
		ft_putendl("zoom out");
	if (keycode == 123)
		ft_putendl("move left");
	if (keycode == 124)
		ft_putendl("move right");
	if (keycode == 126)
		ft_putendl("move up");
	if (keycode == 125)
		ft_putendl("move down");
	//put_map(env, map);
	return (0);
}

void		do_map(t_env *env, t_map *map)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, env->x_win, env->y_win, "| Fdf |");
	env->img = mlx_new_image(env->mlx, env->x_win, env->y_win);
	put_map(env, map);
	mlx_key_hook(env->win, hook_key, 0);
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
//	env->img = mlx_new_image(env->mlx, env->x_win, env->y_win);
	do_map(env, map);
//	mlx_loop(env->mlx);
	return (0);
}
