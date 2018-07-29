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

void	color_style(int keycode, t_mlx *map)
{
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
}

int		key_down(int keycode, t_mlx *map)
{
	color_style(keycode, map);
	if (keycode == 50)
	{
		init_fractal(map);
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

	real_diff = fabs(map->f.min_re - map->f.max_re) * 0.05;
	img_diff = fabs(map->f.min_im - map->f.max_im) * 0.05;
	if (keycode == 123)
	{
		map->f.min_re += real_diff;
		map->f.max_re += real_diff;
	}
	if (keycode == 124)
	{
		map->f.min_re -= real_diff;
		map->f.max_re -= real_diff;
	}
	if (keycode == 125)
	{
		map->f.min_im += img_diff;
		map->f.max_im += img_diff;
	}
	if (keycode == 126)
	{
		map->f.min_im -= img_diff;
		map->f.max_im -= img_diff;
	}
}

int		key_long_press(int keycode, t_mlx *map)
{
	key_move_fractal(keycode, map);
	if (keycode == 12 && map->f.max_iterations < 5000)
	{
		map->f.max_iterations += 10;
	}
	if (keycode == 13 && map->f.max_iterations > 10)
	{
		map->f.max_iterations -= 10;
	}
	empty(map);
	escape_time(map);
	draw_ui(map);
	return (1);
}
