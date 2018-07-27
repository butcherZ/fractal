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

	real_diff = fabs(map->f.MinRe - map->f.MaxRe) * 0.05;
	img_diff = fabs(map->f.MinIm - map->f.MaxIm) * 0.05;
	if (x > MENU_WIDTH && x < (MENU_WIDTH + 20) && map->freez == 1)
	{
		map->f.MinRe -= real_diff;
		map->f.MaxRe -= real_diff;
	}
	if (x < WIN_WIDTH && x > (WIN_WIDTH - 20) && map->freez == 1)
	{
		map->f.MinRe += real_diff;
		map->f.MaxRe += real_diff;
	}
	if (y < 20 && y > 0 && map->freez == 1)
	{
		map->f.MinIm += img_diff;
		map->f.MaxIm += img_diff;
	}
	if (y < WIN_HEIGHT && y > (WIN_HEIGHT - 20) && map->freez == 1)
	{
		map->f.MinIm -= img_diff;
		map->f.MaxIm -= img_diff;
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
** x = 10, cr = -2 + 10 * abs(2 / IMG_WIDTH)
*/

int			mouse_move(int x, int y, t_mlx *map)
{
	map->info.mouse_x = x;
	map->info.mouse_y = y;
	translate_fractal(x, y, map);
	if (map->input == JULIA && map->freez == 0)
	{
		map->f.cr = (double)x * 2 / IMG_WIDTH - 2;
		map->f.ci = (double)y * 2 / IMG_HEIGHT - 2;
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

	cursor_x = map->f.MinRe + (x * ((map->f.MaxRe - map->f.MinRe)
				/ IMG_WIDTH));
	cursor_y = map->f.MaxIm - (y * ((map->f.MaxIm - map->f.MinIm)
				/ IMG_HEIGHT));
	if (button == 4)
	{
		map->fac.count -= 1;
		map->f.MinRe = cursor_x - ((cursor_x - map->f.MinRe) * 1.1);
		map->f.MaxRe = cursor_x + ((map->f.MaxRe - cursor_x) * 1.1);
		map->f.MinIm = cursor_y - ((cursor_y - map->f.MinIm) * 1.1);
		map->f.MaxIm = cursor_y + ((map->f.MaxIm - cursor_y) * 1.1);
	}
	if (button == 5)
	{
		map->fac.count += 1;
		map->f.MinRe = cursor_x - ((cursor_x - map->f.MinRe) / 1.1);
		map->f.MaxRe = cursor_x + ((map->f.MaxRe - cursor_x) / 1.1);
		map->f.MinIm = cursor_y - ((cursor_y - map->f.MinIm) / 1.1);
		map->f.MaxIm = cursor_y + ((map->f.MaxIm - cursor_y) / 1.1);
	}
}

int			mouse_wheel(int button, int x, int y, t_mlx *map)
{
	map->info.mouse_button = button;
	zoom_on_cursor(button, x, y, map);
	if (button == 1)
		map->freez = (map->freez + 1) % 2;
	if (button == 2)
		map->menu = (map->menu + 1) % 2;
	empty(map);
	escape_time(map);
	draw_ui(map);
	return (1);
}
