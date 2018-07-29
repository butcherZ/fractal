/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 07:06:52 by zyuan             #+#    #+#             */
/*   Updated: 2018/07/27 07:08:54 by zyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractol.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int		key_down(int keycode, t_mlx *map)
{
	// printf("keycode is %d\n", keycode);
	if (keycode == 10)
	{
		init_fractal(map);
		map->animated = 0;
	}
	if (keycode == 18)
	{
		map->color.color_style = DEFAULT;
	}
	if (keycode == 19)
	{
		map->color.color_style = STAR_DUST;
	}
	if (keycode == 20)
	{
		map->color.color_style = BLOODY_HELL;
	}
	if (keycode == 21)
	{
		map->color.color_style = CRAZY_MODE;
	}
	if (keycode == 53)
	{
		mlx_destroy_window(map->mlx, map->win);
		exit(1);
	}
	empty(map);
	escape_time(map);
	draw_ui(map);
	return (1);
}

void	key_move_fractal(int keycode, t_mlx *map)
{
	double real_diff;
	double img_diff;

	real_diff = fabs(map->f.MinRe - map->f.MaxRe) * 0.05;
	img_diff = fabs(map->f.MinIm - map->f.MaxIm) * 0.05;
	if (keycode == 123)
	{
		map->f.MinRe += real_diff;
		map->f.MaxRe += real_diff;
	}
	if (keycode == 124)
	{
		map->f.MinRe -= real_diff;
		map->f.MaxRe -= real_diff;
	}
	if (keycode == 125)
	{
		map->f.MinIm += img_diff;
		map->f.MaxIm += img_diff;
	}
	if (keycode == 126)
	{
		map->f.MinIm -= img_diff;
		map->f.MaxIm -= img_diff;
	}
}

int		key_long_press(int keycode, t_mlx *map)
{
	key_move_fractal(keycode, map);
	if (keycode == 12)
	{
		map->f.MaxIterations += 1;
	}
	if (keycode == 13)
	{
		map->f.MaxIterations -= 1;
	}
	empty(map);
	escape_time(map);
	draw_ui(map);
	return (1);
}
