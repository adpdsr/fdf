/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 15:27:50 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/22 13:49:14 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	e_param(int ac, char **env)
{
	if (ac != 2 || !env || !(*env))
	{
		if (ac != 2)
			ft_putendl_fd("usage: ./fdf file1", 2);
		if (!env || !(*env))
			ft_putendl_fd("fdf cant be launch with empty env", 2);
		exit(1);
	}
}

void	e_errno(char *av, char *strerror)
{
	ft_putstr_fd(av, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror, 2);
	exit(1);
}

void	e_map(int err, char *error, int line, int flag)
{
	ft_putstr_fd("invalid map: ", 2);
	if (flag == 1)
		ft_putchar_fd(err, 2);
	else if (flag == 2)
	{
		ft_putstr_fd("line ", 2);
		ft_putnbr_fd(line, 2);
		ft_putstr_fd(" has ", 2);
		ft_putnbr_fd(err, 2);
		if (err > 1)
			ft_putstr_fd(" values", 2);
		else
			ft_putstr_fd(" value", 2);
	}
	ft_putstr_fd(error, 2);
	exit(1);
}
