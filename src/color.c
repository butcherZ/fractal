/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 06:54:09 by zyuan             #+#    #+#             */
/*   Updated: 2018/07/27 06:58:56 by zyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractol.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <string.h>

void			fill_square(t_mlx *map, int width, int height, int color)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < height)
	{
		if (i < width)
		{
			ui_img_put_pixel(map, i, j, color);
			i++;
		}
		else
		{
			i = 0;
			j++;
		}
	}
}

unsigned long	create_rgb(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

/*
** https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/
*/

void			get_color(t_mlx *map)
{
	float	t;

	t = (float)map->f.n / (float)map->f.max_iterations;
	if (map->color.color_style == DEFAULT)
	{
		map->color.r = (int)(9 * (1 - t) * t * t * t * 255);
		map->color.g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		map->color.b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	if (map->color.color_style == STAR_DUST)
	{
		map->color.r = (int)(9 * (1 - t) * t * 112);
		map->color.g = (int)(15 * (1 - t) * (1 - t) * t * t * 250);
		map->color.b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 179);
	}
	if (map->color.color_style == BLOODY_HELL)
	{
		map->color.r = (int)(9 * (1 - t) * t * 175);
		map->color.g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		map->color.b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * t * 205);
	}
}

void			draw(t_mlx *map, int x, int y)
{
	int		i;

	i = 0;
	if (map->f.is_inside != 1)
	{
		if (i < IMG_WIDTH * IMG_HEIGHT)
		{
			img_put_pixel(map, x, y, create_rgb(map->color.r,
						map->color.g, map->color.b));
			i++;
		}
		map->total = i;
	}
}
