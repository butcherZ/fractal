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
**	MinRe left (x)
**	MaxRe right (x)
**	MinIm top (y)
**	MaxIm buttom (y)
*/

void	init_mandelbrot(t_mlx *map)
{
	map->f.MinRe = -2.55;
	map->f.MaxRe = 1.41;
	map->f.MinIm = -1.16;
	map->f.MaxIm = map->f.MinIm + (map->f.MaxRe - map->f.MinRe)
		* IMG_HEIGHT / IMG_WIDTH;
	map->f.MaxIterations = 80;
	map->fac.count = 1;
	map->f.cr = 0;
	map->f.ci = 0;
}

void	init_julia(t_mlx *map)
{
	map->f.MinRe = -4.24;
	map->f.MaxRe = 2.81;
	map->f.MinIm = -2.14;
	map->f.MaxIm = map->f.MinIm + (map->f.MaxRe - map->f.MinRe)
		* IMG_HEIGHT / IMG_WIDTH;
	map->f.MaxIterations = 80;
	map->fac.count = 1;
	map->f.cr = -0.70176;
	map->f.ci = -0.3842;
}

void	init_burningship(t_mlx *map)
{
	map->f.MinRe = -3.70;
	map->f.MaxRe = 2.12;
	map->f.MinIm = -1.60;
	map->f.MaxIm = map->f.MinIm + (map->f.MaxRe - map->f.MinRe)
		* IMG_HEIGHT / IMG_WIDTH;
	map->f.MaxIterations = 80;
	map->fac.count = 1;
	map->f.cr = 0;
	map->f.ci = 0;
}

void	init_var(t_mlx *map)
{
	map->f.c_re = map->f.MinRe + map->img.x * map->f.Re_factor;
	map->f.z_re = map->f.c_re;
	map->f.z_im = map->f.c_im;
	map->f.isInside = 1;
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
