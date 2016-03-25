/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:00:36 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/25 11:39:24 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		build_map(t_map	*map, char **split, int i)
{
	int		j;

	j = -1;
	if (!(map->map[i] = (int *)malloc(sizeof(int) * (map->x))))
		exit(1);
	while (++j < map->x)
		map->map[i][j] = ft_atoi(split[j]);
}

static void	check_line(char **split)
{
	int i;
	int	j;

	i = -1;
	while (split[++i])
	{
		j = -1;
		while (split[i][++j])
			if (!ft_isdigit(split[i][j]) && split[i][j] != '-')
				e_map(split[i][j], ": wrong char\n", 0, 1);
	}
}

static void	read_map(char *av, t_env *env, t_map *map)
{
	char	*line;
	char 	**split;

	while (get_next_line(env->fd, &line) == 1)
	{
		split = ft_strsplit_ws(line);
		if (split)
		{
			ft_strdel(&line);
			check_line(split);
			if (map->x == 0)
				map->x = ft_tablen(split);
			else if (map->x != 0)
				if (map->x != ft_tablen(split))
					e_map(ft_tablen(split), ": all lines must have same lenght\n", map->y, 2);
			ft_freetab(split);
			map->y++;
		}
		else
		{
			ft_putstr_fd(av, 2);
			ft_putendl_fd(": file is empty", 2);
			exit(1);
		}
	}
	close(env->fd);
}

static void	get_map(char *av, t_env *env, t_map *map)
{
	int		i;
	char 	*line;
	char	**split;

	i = 0;
	if ((env->fd = open(av, O_RDONLY)) == -1)
		exit(1);
	if (!(map->map = (int **)malloc(sizeof(int *) * (map->y))))
		exit(1);
	while (get_next_line(env->fd, &line) > 0)
	{
		split = ft_strsplit_ws(line);
		if (split)
			ft_strdel(&line);
		build_map(map, split, i);
		ft_freetab(split);
		i++;
	}
	close(env->fd);
}

t_map		*parsing(char *av, t_env *env)
{
	int 	i;
	int		fd;
	char	*line;
	t_map	*map;

	map = init_map();
	read_map(av, env, map);
	get_map(av, env, map);
	return (map);
}
