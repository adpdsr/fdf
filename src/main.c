/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:00:36 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/28 18:24:05 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void		e_param(int ac, char **env)
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

static t_env	*init_env(char *av)
{
	t_env	*env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		exit(1);
	if ((env->fd = open(av, O_RDONLY)) == -1)
	{
		ft_putendl_fd("fdf: invalid fd", 2);
		exit(1);
	}
	env->y_win = 800;
	env->x_win = 1200;
	return (env);
}

static t_map	*init_map(void)
{
	t_map	*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		exit(1);
	map->l = 0;
	map->h = 0;
	map->zoom = 20;
	map->height = 3;
	map->factor = 0.5;
	map->offset_x = -300;
	map->offset_y = 500;
	return (map);
}

int				main(int ac, char **av, char **environ)
{
	t_map	*map;
	t_env	*env;

	e_param(ac, environ);
	env = init_env(av[1]);
	map = init_map();
	parsing(av[1], env, map);
	do_map(env, map);
	return (0);
}
