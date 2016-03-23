/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:00:36 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/23 18:57:18 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		build_map(t_map	*map, char **split, int i)
{
	int		j;

	j = 0;
	if (!(map->map[i] = (int *)malloc(sizeof(int) * (map->x))))
		exit(1);
	while (j < map->x)
	{
		map->map[i][j] = ft_atoi(split[j]);
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

t_map		*parsing(int ac, char *av, t_env *env)
{
	int 	i;
	int		fd;
	char	*line;
	char	**split;
	t_map	*map;

	split = NULL;
	map = init_map();
	if ((env->fd = open(av, O_RDONLY)) == -1)
		exit(1);
	while (get_next_line(env->fd, &line) == 1)
	{
		split = ft_strsplit_ws(line);
		//ft_strdel(&line);
		check_line(split);
		if (map->x == 0)
			map->x = ft_tablen(split);
		else if (map->x != 0)
			if (map->x != ft_tablen(split))
				e_map(ft_tablen(split), ": all lines must have same lenght\n", map->y, 2);
		//ft_freetab(split);
		map->y++;
	}
	close(env->fd);
	if (split == NULL)
	{
		ft_putstr_fd(av, 2);
		ft_putendl_fd(": file is empty", 2);
		exit(1);
	}
	i = 0;
	if ((env->fd = open(av, O_RDONLY)) == -1)
		exit(1);
	if (!(map->map = (int **)malloc(sizeof(int *) * (map->y))))
		exit(1);
	while (get_next_line(env->fd, &line) > 0)
	{
		split = ft_strsplit_ws(line);
		// ft_strdel(&line);
		build_map(map, split, i);
		ft_freetab(split);
		i++;
	}
	close(env->fd);
	return (map);
}
