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
	map->f.MinRe = -2.0; //LEFT change to zoom
	map->f.MaxRe = 1.0; // RIGHT change to zoom
	map->f.MinIm = -1.2; // TOP
	map->f.MaxIm = map->f.MinIm + (map->f.MaxRe - map->f.MinRe) * IMG_HEIGHT / IMG_WIDTH; // BOTTOM
	map->f.MaxIterations = 50;
	map->fac.count = 1;
	map->f.cr = 0;
	map->f.ci = 0;
}

void init_julia(t_mlx *map)
{
	map->f.MinRe = -2.0; //LEFT change to zoom
	map->f.MaxRe = 1.7; // RIGHT change to zoom
	map->f.MinIm = -1.3; // TOP
	map->f.MaxIm = map->f.MinIm + (map->f.MaxRe - map->f.MinRe) * IMG_HEIGHT / IMG_WIDTH; // BOTTOM
	map->f.MaxIterations = 50;
	map->fac.count = 1;
	map->f.cr = -0.70176;
	map->f.ci = -0.3842;
}

void init_burningship(t_mlx *map)
{
	map->f.MinRe = -2.0; //LEFT change to zoom
	map->f.MaxRe = 1.0; // RIGHT change to zoom
	map->f.MinIm = -0.6; // TOP
	map->f.MaxIm = map->f.MinIm + (map->f.MaxRe - map->f.MinRe) * IMG_HEIGHT / IMG_WIDTH; // BOTTOM
	map->f.MaxIterations = 100;
	map->fac.count = 1;
	map->f.cr = 0;
	map->f.ci = 0;
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

void init(t_mlx *map)
{
	map->f.c_re = map->f.MinRe + map->img.x * map->f.Re_factor;
	map->f.z_re = map->f.c_re; //real part is x
	map->f.z_im = map->f.c_im; //imaginary part is y
	map->f.isInside = 1;
	map->f.n = 0;
}
void set_factor(t_mlx *map)
{
	map->img.y = 0;
	map->f.Re_factor = (map->f.MaxRe - map->f.MinRe) / (IMG_WIDTH - 1);
	map->f.Im_factor = (map->f.MaxIm - map->f.MinIm) / (IMG_HEIGHT - 1);
}

void loop_through(t_mlx *map)
{
	while(map->img.y < IMG_HEIGHT)
	{
			map->f.c_im = map->f.MaxIm - map->img.y * map->f.Im_factor;
			map->img.x = 0;
			while(map->img.x < IMG_WIDTH)
			{
					init(map);
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
// //https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/
			draw(map, map->img.x , map->img.y);
			map->img.x++;
			}
			map->img.y++;
	}
}

void escape_time(t_mlx *map) // this is burning ship
{
	set_factor(map);
	if (map->fac.count % 30 == 0)
	{
			map->f.MaxIterations *= 1.2;
			printf("iterations is %d\n", map->f.MaxIterations);
			printf("count is %d\n", map->fac.count);
	}
	loop_through(map);
}

int			mlx_while(t_mlx *map)
{
	map->index += 1;
	//map->f.MaxIterations = 1;
	if (map->trigger == 1 && map->index > 200)
	{
		map->index = 0;
		if (map->f.MaxIterations <= 30)
			map->f.MaxIterations += 1;
		if (map->f.MaxIterations == 30)
			map->f.MaxIterations -= 1;
		empty(map);
		escape_time(map);
		mlx_put_image_to_window(map->mlx, map->win,
				map->img.img_ptr, 0, 0);
	}
	return (0);
}

int			key_down(int keycode, t_mlx *map)
{
	if (keycode == 10)
	{
		init_mandelbrot(map);
	}
	if (keycode == 48)
	{
		map->trigger = (map->trigger + 1) % 2;
	}
	if (keycode == 53)
	{
		mlx_destroy_window(map->mlx, map->win);
		exit(1);
	}
	empty(map);
	escape_time(map);
	mlx_put_image_to_window(map->mlx, map->win,
			map->img.img_ptr, 0, 0);
	return (1);
}

int			key_long_press(int keycode, t_mlx *map)
{
	double real_diff = fabs(map->f.MinRe - map->f.MaxRe) * 0.05;
	double img_diff = fabs(map->f.MinIm - map->f.MaxIm) * 0.05;
	printf("keycode is %d\n", keycode);
	if (keycode == 18)
	{
		map->fac.count += 1;
		map->f.MinRe -= real_diff;
		map->f.MaxRe += real_diff;
		map->f.MinIm -= img_diff;
		map->f.MaxIm += img_diff;
	}
	if (keycode == 19)
	{
		map->fac.count -= 1;
		map->f.MinRe += real_diff;
		map->f.MaxRe -= real_diff;
		map->f.MinIm += img_diff;
		map->f.MaxIm -= img_diff;
	}
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
	empty(map);
	escape_time(map);
	mlx_put_image_to_window(map->mlx, map->win,
			map->img.img_ptr, 0, 0);
	return (1);
}
void		check_input(t_mlx *map)
{
	char 	*str1;
	char 	*str2;
	char	*str3;

	str1 = "julia";
	str2 = "mandelbrot";
	str3 = "burningship";
	if (ft_strcmp(map->argv, str1) == 0)
			map->input = JULIA;
	else if (ft_strcmp(map->argv, str2) == 0)
			map->input = MANDELBROT;
	else if (ft_strcmp(map->argv, str3) == 0)
			map->input = BURNINGSHIP;
	else
	{
			ft_putstr("invalid argument");
			map->input = 0;
	}
}

int			main(int argc, char *argv[])
{
  t_mlx	map;
	map.index = 0;
	map.trigger = 0;
	map.fac.y_translation = 0;
	map.fac.x_translation = 0;
	map.fac.zoom = 1;
	map.fac.count = 0;
	map.fac.increase_iterations = 1;
	map.mlx = mlx_init();
	map.win = mlx_new_window(map.mlx, WIN_WIDTH, WIN_HEIGHT,
			"is this shit working?");
	if (argc != 2)
	{
			ft_putstr("wrong arguments numbers\n");
			return (-1);
	}
	if (argc == 2)
	{
		map.argv = argv[1];
		check_input(&map);
		if(map.input == 0)
				exit(1);
		else if (map.input == 1)
				init_julia(&map);
		else if(map.input == 2)
				init_mandelbrot(&map);
		else if(map.input == 3)
				init_burningship(&map);
	}
	init_image(&map);
	escape_time(&map);
	//draw(&map);
	mlx_key_hook(map.win, key_down, &map);
	mlx_hook(map.win, 2, 0, key_long_press, &map);
	mlx_put_image_to_window(map.mlx, map.win,
			map.img.img_ptr, 0, 0);
	mlx_loop_hook(map.mlx, mlx_while, &map);
	mlx_loop(map.mlx);
	return (0);
}
