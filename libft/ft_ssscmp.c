/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssscmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 17:54:16 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/12 17:57:32 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ssscmp(char *s, char *s1, char *s2, char *s3)
{
	if (!ft_strcmp(s, s1) || !ft_strcmp(s, s2) || !ft_strcmp(s, s3))
		return (1);
	return (0);
}