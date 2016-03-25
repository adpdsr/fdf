/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 15:29:32 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/25 12:33:54 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_env	*init_env(char *av) // static dans main.c
{
	t_env	*env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		exit(1); // ft exit malloc
	if ((env->fd = open(av, O_RDONLY)) == -1)
		exit(1); // error open
	env->y_win = 800;
	env->x_win = 1200;
	return (env);
}

t_map	*init_map(void)
{
	t_map	*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		exit(1);
	map->x = 0;
	map->y = 0;
	return (map);
}
