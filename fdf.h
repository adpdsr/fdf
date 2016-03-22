/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:21:30 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/22 17:33:03 by adu-pelo         ###   ########.fr       */
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

typedef struct	s_map
{
	int			**map;
	int			x; // largeur
	int			y;  // hauteur
}				t_map;

void	e_map(int err, char *error, int line, int flag);
void	e_errno(char *av, char *strerror);
void	e_param(int ac, char **env);

t_env	*init_env(void);
t_map	*init_map(void);

t_map	*parsing(int ac, char *av, t_env *env);

#endif
