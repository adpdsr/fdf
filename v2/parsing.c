/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:00:36 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/27 19:20:03 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_map   *init_map(void)
{
	t_map   *map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		exit(1);
	map->l = 0;
	map->h = 0;
	map->zoom = 20; // reinit a la fin de read_map
	map->height = 3;
	map->factor = 0.5;
	map->offset_x = -300;
	map->offset_y = 500;
	return (map);
}

static void		build_map(t_map	*map, char **split, int i)
{
	int		k;
	int		j;

	j = 0;
	k = map->l -1;
	if (!(map->map[i] = (int *)malloc(sizeof(int) * (map->l))))
		exit(1);
	while (j < map->l)
	{
		map->map[i][k] = ft_atoi(split[j]);
		k--;
		j++;
	}
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
			if (map->l == 0)
				map->l = ft_tablen(split);
			else if (map->l != 0)
				if (map->l != ft_tablen(split))
					e_map(ft_tablen(split), ": all lines must have same lenght\n", map->h, 2);
			ft_freetab(split);
			map->h++;
		}
		else
		{
			ft_putstr_fd(av, 2);
			ft_putendl_fd(": file is empty", 2);
			exit(1);
		}
	}
	close(env->fd);
	map->zoom = env->x_win / (((map->l + map->h) / 2) * 3);
	printf("zoom = |%d|\n", map->zoom);
}

static void	get_map(char *av, t_env *env, t_map *map)
{
	int		i;
	char 	*line;
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
	map->win = env->win;
	map->mlx = env->mlx;
	return (map);
}
