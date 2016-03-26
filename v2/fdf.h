/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:21:30 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/26 18:22:01 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <stdio.h> // debug

#include <mlx.h>
#include <math.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include "libft/libft.h"

#define BASE_COLOR 0x00FFFFFF

typedef struct	s_seg
{
	float		x1;
	float		x2;
	float		y1;
	float		y2;
	float		z1;
	float		z2;
	float		dx;
	float		dy;
}				t_seg;

typedef struct	s_map
{
	int			**map;
	int			l; // largeur **int map
	int			h; // hauteur **int map
	int			zoom;
	int			height;
	int			offset_x;
	int			offset_y;
	t_seg		seg;
}				t_map;

typedef struct	s_env
{
	int			fd;
	void		*mlx;
	void		*win;
	void		*img;
	int			x_win;
	int			y_win;
	double		x;
	double		y;
}				t_env;

void	do_map(t_env *env, t_map *map);
void	e_errno(char *av, char *strerror);
void	e_map(int err, char *error, int line, int flag);
void	put_map(t_env *env, t_map *map);
t_map	*parsing(char *av, t_env *env);

#endif
