/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:00:36 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/17 18:30:11 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		error_av(char *error)
{
	ft_putendl_fd(error, 2);
	exit(1);
}

static void		error_errno(char *av, char *strerror)
{
	ft_putstr_fd(av, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror, 2);
	exit(1);
}

static t_env	*init_env(void)
{
	t_env	*env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, 1200, 800, "fdf");
	return (env);
}

static void		parsing(int ac, char *av, t_env *env)
{
	int		fd;
	char	*buf;

	if ((fd = open(av, O_RDONLY))== -1)
		error_errno(av, strerror(errno));
	ft_putendl("start parsing");
	buf = ft_strnew(SIZE);
	if (read(fd, buf, SIZE) != -1)
	{
		ft_putendl("read ok");
		ft_putendl(buf);
	}
	else
		ft_putendl("cant read file");
	close(fd);
}

int				main(int ac, char **av)
{
	int x;
	int y;
	t_env	*env;

	if (ac != 2)
		error_av("usage: ./fdf file1");
	env = init_env();
	parsing(ac, av[1], env);
//	y = 50;
//	while (y < 150)
//	{
//		x = 50;
//		while (x < 150)
//		{
//			mlx_pixel_put(env->mlx, env->win, x, y, 0x000FFFFF);
//			x++;
//		}
//		y++;
//	}
	mlx_loop(env->mlx);
	return (0);
}

// stocker chaque ligne de chaque fichier dans 1 maillon d'une liste, stocker aussi la taille de la ligne
