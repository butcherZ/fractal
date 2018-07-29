/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 07:01:46 by zyuan             #+#    #+#             */
/*   Updated: 2018/07/27 07:06:31 by zyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractol.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
**	min_re left (x)
**	max_re right (x)
**	min_im top (y)
**	max_im buttom (y)
*/

void	init_mandelbrot(t_mlx *map)
{
	map->f.min_re = -2.55;
	map->f.max_re = 1.41;
	map->f.min_im = -1.16;
	map->f.max_im = map->f.min_im + (map->f.max_re - map->f.min_re)
		* IMG_HEIGHT / IMG_WIDTH;
	map->f.max_iterations = 80;
	map->fac.count = 1;
	map->f.cr = 0;
	map->f.ci = 0;
	map->color.color_style = DEFAULT;
}

void	init_julia(t_mlx *map)
{
	map->f.min_re = -4.24;
	map->f.max_re = 2.81;
	map->f.min_im = -2.14;
	map->f.max_im = map->f.min_im + (map->f.max_re - map->f.min_re)
		* IMG_HEIGHT / IMG_WIDTH;
	map->f.max_iterations = 80;
	map->fac.count = 1;
	map->f.cr = -0.70176;
	map->f.ci = -0.3842;
	map->color.color_style = DEFAULT;
}

void	init_burningship(t_mlx *map)
{
	map->f.min_re = -3.70;
	map->f.max_re = 2.12;
	map->f.min_im = -1.60;
	map->f.max_im = map->f.min_im + (map->f.max_re - map->f.min_re)
		* IMG_HEIGHT / IMG_WIDTH;
	map->f.max_iterations = 80;
	map->fac.count = 1;
	map->f.cr = 0;
	map->f.ci = 0;
	map->color.color_style = DEFAULT;
}

void	init_var(t_mlx *map)
{
	map->f.c_re = map->f.min_re + map->img.x * map->f.re_factor;
	map->f.z_re = map->f.c_re;
	map->f.z_im = map->f.c_im;
	map->f.is_inside = 1;
	map->f.n = 0;
}

void	init_fractal(t_mlx *map)
{
	if (map->input == 0)
		exit(1);
	else if (map->input == JULIA)
		init_julia(map);
	else if (map->input == MANDELBROT)
		init_mandelbrot(map);
	else if (map->input == BURNINGSHIP)
		init_burningship(map);
}
