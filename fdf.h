/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:21:30 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/25 12:33:53 by adu-pelo         ###   ########.fr       */
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
	int			x; // nb num / ligne
	int			y; // nb ligne
	float		x_range; // != entre min X et max X
	float		y_range; // != entre min Y et max Y
	float		coef;	 // distance entre 2 pixel
	float		x_offset;
	float		y_offset;
}				t_map;

void	e_param(int ac, char **env);
void	e_errno(char *av, char *strerror);
void	e_map(int err, char *error, int line, int flag);

t_env	*init_env(char *av); // static
t_map	*init_map(void); // static
t_map	*parsing(char *av, t_env *env);

#endif
