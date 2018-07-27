#include "mlx.h"
#include "fractol.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long createRGB(int r, int g, int b)
{
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

/*
** https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/
*/

void get_color(t_mlx *map)
{
	float t = (float)map->f.n / (float)map->f.MaxIterations;

	map->color.r = (int)(9*(1-t)*t*t*t*255);
	map->color.g = (int)(15*(1-t)*(1-t)*t*t*255);
	map->color.b =  (int)(8.5*(1-t)*(1-t)*(1-t)*t*255);
}

void draw(t_mlx *map, int x, int y)
{
	int i = 0;
	if(map->f.isInside != 1)
	{
		if (i < IMG_WIDTH * IMG_HEIGHT)
		{
			img_put_pixel(map, x, y, createRGB(map->color.r, map->color.g, map->color.b));
			i++;
		}
			map->total = i;
	}
}
