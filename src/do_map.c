/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 15:23:58 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/28 18:24:56 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void			do_map(t_env *env, t_map *map)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, env->x_win, env->y_win, "| Fdf |");
	map->mlx = env->mlx;
	map->win = env->win;
	put_map(map);
	mlx_key_hook(env->win, &hook_key, map);
	mlx_loop(env->mlx);
}
