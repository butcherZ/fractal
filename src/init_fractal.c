#include "mlx.h"
#include "fractol.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	init_mandelbrot(t_mlx *map)
{
	map->f.MinRe = -2.55; //LEFT change to zoom
	map->f.MaxRe = 1.41; // RIGHT change to zoom
	map->f.MinIm = -1.16; // TOP
	map->f.MaxIm = map->f.MinIm + (map->f.MaxRe - map->f.MinRe) * IMG_HEIGHT / IMG_WIDTH; // BOTTOM
	map->f.MaxIterations = 80;
	map->fac.count = 1;
	map->f.cr = 0;
	map->f.ci = 0;
}

void init_julia(t_mlx *map)
{
	map->f.MinRe = -3.91; //LEFT
	map->f.MaxRe = 5.49; // RIGHT
	map->f.MinIm = -2.9; // TOP
	map->f.MaxIm = map->f.MinIm + (map->f.MaxRe - map->f.MinRe) * IMG_HEIGHT / IMG_WIDTH; // BOTTOM
	map->f.MaxIterations = 80;
	map->fac.count = 1;
	map->f.cr = -0.70176;
	map->f.ci = -0.3842;
}

void init_burningship(t_mlx *map)
{
	map->f.MinRe = -2.54; //LEFT change to zoom
	map->f.MaxRe = 3.29; // RIGHT change to zoom
	map->f.MinIm = -1.43; // TOP
	map->f.MaxIm = map->f.MinIm + (map->f.MaxRe - map->f.MinRe) * IMG_HEIGHT / IMG_WIDTH; // BOTTOM
	map->f.MaxIterations = 80;
	map->fac.count = 1;
	map->f.cr = 0;
	map->f.ci = 0;
}

void init_var(t_mlx *map)
{
	map->f.c_re = map->f.MinRe + map->img.x * map->f.Re_factor;
	map->f.z_re = map->f.c_re; //real part is x
	map->f.z_im = map->f.c_im; //imaginary part is y
	map->f.isInside = 1;
	map->f.n = 0;
}

void		init_fractal(t_mlx *map)
{
	if(map->input == 0)
			exit(1);
	else if (map->input == JULIA)
			init_julia(map);
	else if(map->input == MANDELBROT)
			init_mandelbrot(map);
	else if(map->input == BURNINGSHIP)
			init_burningship(map);
}
