/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 06:59:19 by zyuan             #+#    #+#             */
/*   Updated: 2018/07/27 07:01:21 by zyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractol.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void		check_map(t_mlx *map)
{
	map->f.z_re_square = map->f.z_re * map->f.z_re;
	map->f.z_im_square = map->f.z_im * map->f.z_im;
	if (map->input == JULIA)
	{
		map->f.z_im = 2 * map->f.z_re * map->f.z_im + map->f.ci;
		map->f.z_re = map->f.z_re_square - map->f.z_im_square + map->f.cr;
	}
	else if (map->input == MANDELBROT)
	{
		map->f.z_im = 2 * map->f.z_re * map->f.z_im + map->f.c_im;
		map->f.z_re = map->f.z_re_square - map->f.z_im_square + map->f.c_re;
	}
	else if (map->input == BURNINGSHIP)
	{
		map->f.z_im = 2 * fabs(map->f.z_re * map->f.z_im) - map->f.c_im;
		map->f.z_re = map->f.z_re_square - map->f.z_im_square + map->f.c_re;
	}
}

void		loop_through(t_mlx *map)
{
	while (map->img.y < IMG_HEIGHT)
	{
		map->f.c_im = map->f.max_im - map->img.y * map->f.im_factor;
		map->img.x = 0;
		while (map->img.x < IMG_WIDTH)
		{
			init_var(map);
			while (map->f.n < map->f.max_iterations)
			{
				check_map(map);
				if (map->f.z_re_square + map->f.z_im_square > 4)
				{
					map->f.is_inside = 0;
					break ;
				}
				map->f.n++;
			}
			get_color(map);
			draw(map, map->img.x, map->img.y);
			map->img.x++;
		}
		map->img.y++;
	}
}

void		set_factor(t_mlx *map)
{
	map->img.y = 0;
	map->f.re_factor = (map->f.max_re - map->f.min_re) / (IMG_WIDTH - 1);
	map->f.im_factor = (map->f.max_im - map->f.min_im) / (IMG_HEIGHT - 1);
}

void		increase_iterations(t_mlx *map)
{
	map->flag = 0;
	if (map->fac.count % 30 == 0)
	{
		if (map->info.mouse_button == 5 && map->flag == 0
			&& map->f.max_iterations < 5000)
		{
			printf("this is 5\n");
			map->flag = 1;
			map->f.max_iterations += 20;
		}
		if (map->info.mouse_button == 4 && map->flag == 0
			&& map->f.max_iterations >= 20)
		{
			printf("this is 4\n");
			map->flag = 1;
			map->f.max_iterations -= 20;
		}
	}
}

/*
** remove increase_iterations() in escape_time to gain more speed of the program
*/

void		escape_time(t_mlx *map)
{
	increase_iterations(map);
	set_factor(map);
	loop_through(map);
	mlx_put_image_to_window(map->mlx, map->win,
			map->img.img_ptr, 0, 0);
}
