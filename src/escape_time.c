#include "mlx.h"
#include "fractol.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_map(t_mlx *map)
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

void loop_through(t_mlx *map)
{
	while(map->img.y < IMG_HEIGHT)
	{
			map->f.c_im = map->f.MaxIm - map->img.y * map->f.Im_factor;
			map->img.x = 0;
			while(map->img.x < IMG_WIDTH)
			{
					init_var(map);
					while(map->f.n < map->f.MaxIterations)
					{
						check_map(map);
						if(map->f.z_re_square + map->f.z_im_square > 4)
						{
								 map->f.isInside = 0;
								 break;
						 }
						 map->f.n++;
					}
			get_color(map);
			draw(map, map->img.x , map->img.y);
			map->img.x++;
			}
			map->img.y++;
	}
}

void set_factor(t_mlx *map)
{
	map->img.y = 0;
	map->f.Re_factor = (map->f.MaxRe - map->f.MinRe) / (IMG_WIDTH - 1);
	map->f.Im_factor = (map->f.MaxIm - map->f.MinIm) / (IMG_HEIGHT - 1);
}

void increase_iterations(t_mlx *map)
{
	int flag = 0;
	if (map->fac.count % 30 == 0)
	{
		if (map->info.mouse_button == 5 && flag == 0)
		{
			flag = 1;
			map->f.MaxIterations *= 1.2;
		}
		if  (map->info.mouse_button == 4 && flag == 0)
		{
			flag = 1;
			map->f.MaxIterations /= 1.2;
		}
	}
}

void escape_time(t_mlx *map)
{
	increase_iterations(map);
	set_factor(map);
	loop_through(map);
	mlx_put_image_to_window(map->mlx, map->win,
			map->img.img_ptr, 0, 0);
}