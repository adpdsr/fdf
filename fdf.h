/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:21:30 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/23 18:57:16 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <stdio.h> // debug

#include <mlx.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef struct	s_env
{
	int			fd;
	void		*mlx;
	void		*win;
	void		*img;
	int			x_win;
	int			y_win;
}				t_env;

typedef struct	s_pts
{
	int			x_pts;
	int			y_pts;
	int			z_pts;
	float		X;
	float		Y;
}				t_pts;

typedef struct	s_map
{
	t_pts		**point;
	int			**map;
	int			x; // largeur
	int			y; // hauteur
}				t_map;

void	e_param(int ac, char **env);
void	e_errno(char *av, char *strerror);
void	e_map(int err, char *error, int line, int flag);

t_env	*init_env(void);
t_map	*init_map(void);
t_map	*parsing(int ac, char *av, t_env *env);

#endif
