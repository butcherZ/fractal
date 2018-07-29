/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 07:23:59 by zyuan             #+#    #+#             */
/*   Updated: 2018/07/27 07:27:21 by zyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractol.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void		fill_square(t_mlx *map, int width, int height, int color)
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

void		print_info(t_mlx *map)
{
	int		var_color;

	var_color = 0xFFAFBD;
	mlx_string_put(map->mlx, map->win, 15, 30, 0x74ebd5, "informations: ");
	mlx_string_put(map->mlx, map->win, 35, 70, 0xFFFFFF, "current fractal: ");
	mlx_string_put(map->mlx, map->win, 205, 70, var_color, map->argv);
	mlx_string_put(map->mlx, map->win, 35, 100, 0xFFFFFF, "mouse X: ");
	mlx_string_put(map->mlx, map->win, 125, 100, var_color,
			ft_itoa(map->info.mouse_x));
	mlx_string_put(map->mlx, map->win, 35, 130, 0xFFFFFF, "mouse Y: ");
	mlx_string_put(map->mlx, map->win, 125, 130, var_color,
			ft_itoa(map->info.mouse_y));
	mlx_string_put(map->mlx, map->win, 35, 160, 0xFFFFFF, "Max iterations: ");
	mlx_string_put(map->mlx, map->win, 195, 160, var_color,
			ft_itoa(map->f.max_iterations));
	mlx_string_put(map->mlx, map->win, 35, 190, 0xFFFFFF, "Zoom: ");
	mlx_string_put(map->mlx, map->win, 95, 190, var_color,
			ft_itoa((pow(1.1, map->fac.count) * 100) - 10));
	mlx_string_put(map->mlx, map->win, 175, 190, 0xFFFFFF, "%");
	mlx_string_put(map->mlx, map->win, 35, 220, 0xFFFFFF, "Freeze Image: ");
	if (map->freeze == 0)
		mlx_string_put(map->mlx, map->win, 175, 220, var_color, "OFF");
	else
		mlx_string_put(map->mlx, map->win, 175, 220, var_color, "ON");
}

void		print_control(t_mlx *map)
{
	int		var_color;

	var_color = 0xFFAFBD;
	mlx_string_put(map->mlx, map->win, 15, 260, 0x74ebd5, "Controls: ");
	mlx_string_put(map->mlx, map->win, 35, 300, 0xFFFFFF, "Zoom In: ");
	mlx_string_put(map->mlx, map->win, 35, 325, var_color, "Scroll up wheel");
	mlx_string_put(map->mlx, map->win, 35, 350, 0xFFFFFF, "Zoom Out: ");
	mlx_string_put(map->mlx, map->win, 35, 375, var_color, "Scroll down wheel");
	mlx_string_put(map->mlx, map->win, 35, 400, 0xFFFFFF, "Move: ");
	mlx_string_put(map->mlx, map->win, 35, 425, var_color, "Arrow Keys");
	mlx_string_put(map->mlx, map->win, 35, 450, 0xFFFFFF, "Reset: ");
	mlx_string_put(map->mlx, map->win, 35, 475, var_color, " ` ");
	mlx_string_put(map->mlx, map->win, 35, 500, 0xFFFFFF, "Freeze Image: ");
	mlx_string_put(map->mlx, map->win, 35, 525, var_color, "left click mouse");
	mlx_string_put(map->mlx, map->win, 35, 550, 0xFFFFFF, "Hide / Show menu: ");
	mlx_string_put(map->mlx, map->win, 35, 575, var_color, "right click mouse");
	mlx_string_put(map->mlx, map->win, 35, 600, 0xFFFFFF, "+ / - iterations: ");
	mlx_string_put(map->mlx, map->win, 35, 625, var_color, "Q/W");
	mlx_string_put(map->mlx, map->win, 15, 665, 0x74ebd5, "Color Styles: ");
	mlx_string_put(map->mlx, map->win, 35, 695, 0xFFFFFF, "Default: ");
	mlx_string_put(map->mlx, map->win, 170, 695, var_color, "1");
	mlx_string_put(map->mlx, map->win, 35, 720, 0xFFFFFF, "Star Dust: ");
	mlx_string_put(map->mlx, map->win, 170, 720, var_color, "2");
	mlx_string_put(map->mlx, map->win, 35, 745, 0xFFFFFF, "Bloody Hell: ");
	mlx_string_put(map->mlx, map->win, 170, 745, var_color, "3");
}

void		draw_ui(t_mlx *map)
{
	if (map->menu == ON)
	{
		mlx_put_image_to_window(map->mlx, map->win,
						map->ui_img.img_ptr, 0, 0);
		print_info(map);
		print_control(map);
	}
}

void		init_ui(t_mlx *map)
{
	init_image_ui(map, MENU_WIDTH, MENU_HEIGHT);
	fill_square(map, MENU_WIDTH, MENU_HEIGHT, 0x66181818);
}
