/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 15:24:25 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/28 18:24:09 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void		build_map(t_map *map, char **split, int i)
{
	int		j;

	j = -1;
	if (!(map->map[i] = (int *)malloc(sizeof(int) * (map->l))))
		exit(1);
	while (++j < map->l)
		map->map[i][j] = ft_atoi(split[j]);
}

static void		check_line(char **split)
{
	int i;
	int	j;

	i = -1;
	while (split[++i])
	{
		j = 0;
		while (split[i][j] && split[i][j] != ',')
		{
			if (!ft_isdigit(split[i][j]) && split[i][j] != '-')
				e_map(split[i][j], ": wrong char\n", 0, 1);
			j++;
		}
	}
}

static void		read_map(char *av, t_env *env, t_map *map, int empty)
{
	char	*line;
	char	**split;

	while (get_next_line(env->fd, &line) == 1)
	{
		empty = 0;
		split = ft_strsplit_ws(line);
		if (split)
		{
			ft_strdel(&line);
			check_line(split);
			if (map->l == 0)
				map->l = ft_tablen(split);
			else if (map->l != 0)
				if (map->l != ft_tablen(split))
					e_map(ft_tablen(split),
					": all lines must have same lenght\n", map->h, 2);
			ft_freetab(split);
			map->h++;
		}
	}
	close(env->fd);
	if (empty)
		e_empty(av, 2);
	map->zoom = env->x_win / (((map->l + map->h) / 2) * 3);
}

static void		get_map(char *av, t_env *env, t_map *map)
{
	int		i;
	char	*line;
	char	**split;

	i = 0;
	if ((env->fd = open(av, O_RDONLY)) == -1)
		exit(1);
	if (!(map->map = (int **)malloc(sizeof(int *) * (map->h))))
		exit(1);
	while (get_next_line(env->fd, &line) > 0)
	{
		split = ft_strsplit_ws(line);
		if (split)
			ft_strdel(&line);
		build_map(map, split, map->h - 1 - i);
		ft_freetab(split);
		i++;
	}
	close(env->fd);
}

void			parsing(char *av, t_env *env, t_map *map)
{
	read_map(av, env, map, 1);
	get_map(av, env, map);
	map->win = env->win;
	map->mlx = env->mlx;
}
