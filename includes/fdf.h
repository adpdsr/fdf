/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:21:30 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/28 18:23:22 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h"

# define BASE_COLOR 0x00FFFFFF
# define ORANGE 0x00FF5B2B
# define L_BLUE 0x005EB6DD
# define D_BLUE 0x00046380
# define RED 0x00B9121B

typedef struct	s_seg
{
	int			x1;
	int			x2;
	int			y1;
	int			y2;
	int			z1;
	int			z2;
	int			dx;
	int			dy;
}				t_seg;

typedef struct	s_map
{
	int			l;
	int			h;
	int			**map;
	void		*mlx;
	void		*win;
	int			zoom;
	int			color;
	int			height;
	int			offset_x;
	int			offset_y;
	double		factor;
	t_seg		seg;
}				t_map;

typedef struct	s_env
{
	int			fd;
	void		*mlx;
	void		*win;
	int			x_win;
	int			y_win;
}				t_env;

int				get_color(t_map *map);
int				hook_key(int keycode, t_map *map);

void			put_map(t_map *map);
void			e_empty(char *ac, int fd);
void			do_map(t_env *env, t_map *map);
void			e_errno(char *av, char *strerror);
void			parsing(char *av, t_env *env, t_map *map);
void			e_map(int err, char *error, int line, int flag);

#endif
