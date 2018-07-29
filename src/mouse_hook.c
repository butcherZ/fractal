/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 07:16:37 by zyuan             #+#    #+#             */
/*   Updated: 2018/07/27 07:22:06 by zyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractol.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void		translate_fractal(int x, int y, t_mlx *map)
{
	double	real_diff;
	double	img_diff;

	real_diff = fabs(map->f.min_re - map->f.max_re) * 0.05;
	img_diff = fabs(map->f.min_im - map->f.max_im) * 0.05;
	if (x > MENU_WIDTH && x < (MENU_WIDTH + 20) && map->freeze == 1)
	{
		map->f.min_re -= real_diff;
		map->f.max_re -= real_diff;
	}
	if (x < WIN_WIDTH && x > (WIN_WIDTH - 20) && map->freeze == 1)
	{
		map->f.min_re += real_diff;
		map->f.max_re += real_diff;
	}
	if (y < 20 && y > 0 && map->freeze == 1)
	{
		map->f.min_im += img_diff;
		map->f.max_im += img_diff;
	}
	if (y < WIN_HEIGHT && y > (WIN_HEIGHT - 20) && map->freeze == 1)
	{
		map->f.min_im -= img_diff;
		map->f.max_im -= img_diff;
	}
}

/*
** x range is 0 to IMG_WIDTH
** y range is 0 to IMG_HEIGHT
** ci range is (-2 to 2)
** cr range is (-2 to 2)
** when x = 0, cr = -2
** x = IMG_WIDTH , cr = 2
** y = 0, ci = -2
** y = IMG_HEIGHT, cr = 2
** whenever x + 1, cr + abs(-2 / IMG_WIDTH)
** y + 1, ci + abs(-2 / IMG_HEIGHT)
** x + 1 = cr + abs(-2 / IMG_WIDTH)
** x = 0, cr = -2
** x = 10, cr = -2 + 10 * abs( -2 / IMG_WIDTH)
** cr = -2 + x * abs( -2 /IMG_WIDTH);
** cr = x * (-2/ IMG_WIDTH) -2 ;
*/

int			mouse_move(int x, int y, t_mlx *map)
{
	map->info.mouse_x = x;
	map->info.mouse_y = y;
	translate_fractal(x, y, map);
	if (map->input == JULIA && map->freeze == 0)
	{
		map->f.cr = (double)x * 4 / IMG_WIDTH - 2;
		map->f.ci = (double)y * 4 / IMG_HEIGHT - 2;
	}
	empty(map);
	escape_time(map);
	draw_ui(map);
	return (1);
}

void		zoom_on_cursor(int button, int x, int y, t_mlx *map)
{
	double	cursor_x;
	double	cursor_y;

	cursor_x = map->f.min_re + (x * ((map->f.max_re - map->f.min_re)
				/ IMG_WIDTH));
	cursor_y = map->f.max_im - (y * ((map->f.max_im - map->f.min_im)
				/ IMG_HEIGHT));
	if (button == 4)
	{
		map->fac.count -= 1;
		map->f.min_re = cursor_x - ((cursor_x - map->f.min_re) * 1.1);
		map->f.max_re = cursor_x + ((map->f.max_re - cursor_x) * 1.1);
		map->f.min_im = cursor_y - ((cursor_y - map->f.min_im) * 1.1);
		map->f.max_im = cursor_y + ((map->f.max_im - cursor_y) * 1.1);
	}
	if (button == 5)
	{
		map->fac.count += 1;
		map->f.min_re = cursor_x - ((cursor_x - map->f.min_re) / 1.1);
		map->f.max_re = cursor_x + ((map->f.max_re - cursor_x) / 1.1);
		map->f.min_im = cursor_y - ((cursor_y - map->f.min_im) / 1.1);
		map->f.max_im = cursor_y + ((map->f.max_im - cursor_y) / 1.1);
	}
}

int			mouse_wheel(int button, int x, int y, t_mlx *map)
{
	map->info.mouse_button = button;
	zoom_on_cursor(button, x, y, map);
	if (button == 1)
		map->freeze = (map->freeze + 1) % 2;
	if (button == 2)
		map->menu = (map->menu + 1) % 2;
	empty(map);
	escape_time(map);
	draw_ui(map);
	return (1);
}
