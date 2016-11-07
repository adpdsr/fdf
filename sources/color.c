/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 15:13:53 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/11/07 16:49:50 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		get_color(t_map *map)
{
	if (map->seg.z1 > 0 && map->seg.z2 > 0)
		return (RED);
	else if (map->seg.z1 > 0 || map->seg.z2 > 0)
		return (ORANGE);
	else if (map->seg.z1 < 0 && map->seg.z2 < 0)
		return (D_BLUE);
	else if (map->seg.z1 < 0 || map->seg.z2 < 0)
		return (L_BLUE);
	else
		return (BASE_COLOR);
}
