#include "mlx.h"
#include "fractol.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
** That is, I define that the minimum real part of the complex numbers (that is,
** the left border of the image) is -2.0 and the maximum (that is, the right
** border) is 1.0. This means that the real part of the complex numbers will go
** from -2.0 to 1.0.
** In the same way I defined that the lower border of the image is equivalent to
** the imaginary part -1.2.
**/
void init_mandelbrot(t_mlx *map)
{
	map->f.MinRe = -2.0;
	map->f.MaxRe = 1.0 * map->fac.zoom; //change to zoom
	map->f.MinIm = -1.2;
	map->f.MaxIm = map->f.MinIm + (map->f.MaxRe - map->f.MinRe) * IMG_HEIGHT / IMG_WIDTH;
	map->f.Re_factor = (map->f.MaxRe - map->f.MinRe) / (IMG_WIDTH - 1);
	map->f.Im_factor = (map->f.MaxIm - map->f.MinIm) / (IMG_HEIGHT - 1);
	map->f.MaxIterations = 50;
}

unsigned long createRGB(int r, int g, int b)
{
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}
/*f(z) = z2 + c;*/

double	square(double nb)
{
		nb = nb * nb;
		return (nb);
}

void get_color(t_mlx *map)
{
	float t = (float)map->f.n / (float)map->f.MaxIterations;

	map->color.r = (int)(9*(1-t)*t*t*t*255);
	map->color.g = (int)(15*(1-t)*(1-t)*t*t*255);
	map->color.b =  (int)(8.5*(1-t)*(1-t)*(1-t)*t*255);
}

void mandelbrot(t_mlx *map)
{
	t_coordinate *coord;
	if (!(coord = malloc(sizeof(t_coordinate) * IMG_WIDTH * IMG_HEIGHT)))
		exit(1);
	int i = 0;
	init_mandelbrot(map);
	int y = 0;

	while(y < IMG_HEIGHT)
	{
	    map->f.c_im = map->f.MaxIm - y * map->f.Im_factor;
			int x = 0;
	    while(x < IMG_WIDTH)
	    {
	        map->f.c_re = map->f.MinRe + x * map->f.Re_factor;
					map->f.z_re = map->f.c_re;
					map->f.z_im = map->f.c_im;
	       map->f.isInside = 1;
					map->f.n = 0;
	        while(map->f.n < map->f.MaxIterations)
	        {
					map->f.z_re_square = map->f.z_re * map->f.z_re;
					map->f.z_im_square = map->f.z_im * map->f.z_im;
	            if(map->f.z_re_square + map->f.z_im_square > 4)
	            {
	               map->f.isInside = 0;
	                break;
	            }
	            map->f.z_im = 2 * map->f.z_re * map->f.z_im + map->f.c_im;
	            map->f.z_re = map->f.z_re_square - map->f.z_im_square + map->f.c_re;
							map->f.n++;
					}
			get_color(map);
// //https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/

		  if(map->f.isInside != 1)
			{
					if (i < IMG_WIDTH * IMG_HEIGHT)
					{
						coord[i].x = x;
						coord[i].y = y;
					img_put_pixel(map, coord[i].x + map->fac.x_translation, coord[i].y + map->fac.y_translation, createRGB(map->color.r, map->color.g, map->color.b));
					//	printf("coord x is %d, coord y is %d\n", coord[i].x, coord[i].y);
						//printf("i is %d\n", i);
						i++;
					}
					map->coord = coord;
					map->total = i;
			}
			x++;
	    }
			y++;
	}
	//free(coord);
}

void draw(t_mlx *map)
{
			int i = 0;
			while (i < map->total)
			{
				img_put_pixel(map, map->coord[i].x, map->coord[i].y, createRGB(map->color.r, map->color.g, map->color.b));
				i++;

			}
}

int			key_down(int keycode, t_mlx *map)
{
	printf("keycode is %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(map->mlx, map->win);
		exit(1);
	}
	if (keycode == 18)
	{
		map->fac.zoom = map->fac.zoom - 0.1;
	}
	if (keycode == 123)
	{
			map->fac.x_translation -= 10;
	}
	if (keycode == 124)
	{
			map->fac.x_translation += 10;
	}
	if (keycode == 125)
	{
			map->fac.y_translation += 10;
	}
	if (keycode == 126)
	{
			map->fac.y_translation -= 10;
	}
	empty(map);
	mandelbrot(map);
	mlx_put_image_to_window(map->mlx, map->win,
			map->img.img_ptr, 0, 0);
	return (1);
}

int			main(void)
{
  t_mlx	map;
	map.fac.zoom = 1;
	map.mlx = mlx_init();
	map.win = mlx_new_window(map.mlx, WIN_WIDTH, WIN_HEIGHT,
			"is this shit working?");
	init_image(&map);
	//fill_screen(&map);
	mandelbrot(&map);
	//draw(&map);
	mlx_key_hook(map.win, key_down, &map);
	mlx_put_image_to_window(map.mlx, map.win,
			map.img.img_ptr, 0, 0);
	mlx_loop(map.mlx);
	return (0);
}
