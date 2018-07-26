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

/**
notes: 1. remove animation?
		2. hit a key to display info
		3. handle blinking when there are other function has benn called
		4. remove sidebar or keep it for displaying Usage ?
		5. add mouse coordinates and keycode to a struct so they could be displayed later;
**/

void	init_mandelbrot(t_mlx *map)
{
	map->f.MinRe = -2.55; //LEFT change to zoom
	map->f.MaxRe = 1.41; // RIGHT change to zoom
	map->f.MinIm = -1.16; // TOP
	map->f.MaxIm = map->f.MinIm + (map->f.MaxRe - map->f.MinRe) * IMG_HEIGHT / IMG_WIDTH; // BOTTOM
	map->f.MaxIterations = 30;
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
	map->f.MaxIterations = 30;
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
	map->f.MaxIterations = 30;
	map->fac.count = 1;
	map->f.cr = 0;
	map->f.ci = 0;
}

void	set_max_iterations(t_mlx *map)
{
	if (map->trigger == 1 && map->animated == 0)
	{
		map->f.MaxIterations = 1;
		map->animated = 1;
	}
	else if (map->trigger == 1 && map->animated == 1)
	{
		if (map->f.MaxIterations < 30)
			map->f.MaxIterations += 1;
		if (map->f.MaxIterations == 30)
			map->f.MaxIterations = 1;
	}
//	else if (map->trigger == 0 && map->animated == 0)
	//	map->f.MaxIterations = 30;
}

void		init_fractol(t_mlx *map)
{
	if(map->input == 0)
			exit(1);
	else if (map->input == JULIA)
			init_julia(map);
	else if(map->input == MANDELBROT)
			init_mandelbrot(map);
	else if(map->input == BURNINGSHIP)
			init_burningship(map);
	set_max_iterations(map);
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

void increase_iterations(t_mlx *map)
{
//	printf("count is %d\n", map->fac.count);
	int flag = 0;
	if (map->fac.count % 30 == 0)
	{
		if (map->info.mouse_button == 4 && flag == 0)
		{
			flag = 1;
			map->f.MaxIterations *= 1.2;
		}
		if  (map->info.mouse_button == 5 && flag == 0)
		{
			flag = 1;
			map->f.MaxIterations /= 1.2;
		}
	}
}

void escape_time(t_mlx *map) // this is burning ship
{
	set_factor(map);
	set_max_iterations(map);
	increase_iterations(map);
	loop_through(map);
	mlx_put_image_to_window(map->mlx, map->win,
			map->img.img_ptr, WIN_WIDTH / 4, 0);
}

int			mlx_while(t_mlx *map)
{
	map->index += 1;
	//map->f.MaxIterations = 1;
	if (map->trigger == 1 && map->index > 200)
	{
	//	printf("MaxIterations is %d\n", map->f.MaxIterations);
		map->index = 0;
	}
	//draw_ui(map);
	empty(map);
	escape_time(map);
	//mlx_string_put(map->mlx, map->win, 500, 10, 0xFFFFFF, ft_itoa(map->index));
	return (0);
}

int			key_down(int keycode, t_mlx *map)
{
	if (keycode == 50)
	{
		init_fractol(map);
		map->animated = 0;
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
	return (1);
}

int			key_long_press(int keycode, t_mlx *map)
{
	double real_diff = fabs(map->f.MinRe - map->f.MaxRe) * 0.05;
	double img_diff = fabs(map->f.MinIm - map->f.MaxIm) * 0.05;
	//printf("keycode is %d\n", keycode);
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
	return (1);
}

void 		print_usage(void)
{
		ft_putstr("Usage: \n");
		ft_putstr("pass fractal's name as argument to lauch desired fractal\nOptions are :\n");
		ft_putstr("- julia\n- mandelbrot\n- burningship\n");
		ft_putstr("Example: ./fractol julia");
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
			ft_putstr("Sorry, this program is too stupid to generate this fractal\n");
			print_usage();
			map->input = 0;
	}
}
/*x range is 0 to IMG_WIDTH
y range is 0 to IMG_HEIGHT
ci range is (-2 to 2)
cr range is (-2 to 2)
when x = 0, cr = -2
	x = IMG_WIDTH , cr = 2
y = 0, ci = -2
	y = IMG_HEIGHT, cr = 2
whenever x + 1, cr + abs(-2 / IMG_WIDTH)
		y + 1, ci + abs(-2 / IMG_HEIGHT)
		x + 1 = cr + abs(-2 / IMG_WIDTH)
		x = 0, cr = -2
		x = 10, cr = -2 + 10 * abs(2 / IMG_WIDTH)*/

int		 mouse_move(int x, int y, t_mlx *map)
{
	//printf("x is %d, y is %d\n", x, y);
	map->info.mouse_x = x;
	map->info.mouse_y = y;
	double real_diff = fabs(map->f.MinRe - map->f.MaxRe) * 0.05;
	double img_diff = fabs(map->f.MinIm - map->f.MaxIm) * 0.05;
	int hotarea;
	hotarea = 20;
	if(map->input == JULIA && map->freez == 0)
	{
		map->f.cr = (double)x * 2 / IMG_WIDTH - 2;
		map->f.ci = (double)y * 2 / IMG_HEIGHT -2;
	}
	if (x > MENU_WIDTH && x < (MENU_WIDTH + hotarea) && map->freez == 1)
	{
		map->f.MinRe -= real_diff;
		map->f.MaxRe -= real_diff;
	}
	if (x < WIN_WIDTH && x > (WIN_WIDTH - hotarea) && map->freez == 1)
	{
		map->f.MinRe += real_diff;
		map->f.MaxRe += real_diff;
	}
	if (y < hotarea && y > 0 && map->freez == 1)
	{
		map->f.MinIm += img_diff;
		map->f.MaxIm += img_diff;
	}
	if (y < WIN_HEIGHT && y > (WIN_HEIGHT - 10) && map->freez == 1)
	{
		map->f.MinIm -= img_diff;
		map->f.MaxIm -= img_diff;
	}
	//printf("cr is %f, ci is %f\n", map->f.cr, map->f.ci);
	empty(map);
	escape_time(map);
	draw_ui(map);
	return (1);
}

int 	mouse_wheel(int button, int x, int y, t_mlx *map)
{
//	printf("button is %d\n", button);
 	double real_diff = fabs(map->f.MinRe - map->f.MaxRe) * 0.05;
	double img_diff = fabs(map->f.MinIm - map->f.MaxIm) * 0.05;
	map->info.mouse_button = button;
	if (button == 5)
	{
		map->fac.count -= 1;
		map->f.MinRe -= real_diff;
		map->f.MaxRe += real_diff;
		map->f.MinIm -= img_diff;
		map->f.MaxIm += img_diff;
		printf("max im is %f\n", map->f.MaxIm);
	}
	if (button == 4)
	{
		map->fac.count += 1;
		map->f.MinRe += real_diff;
		map->f.MaxRe -= real_diff;
		map->f.MinIm += img_diff;
		map->f.MaxIm -= img_diff;
	}
	if (button == 1)
	{
			map->freez= (map->freez + 1) % 2;
	}
	empty(map);
	escape_time(map);
	draw_ui(map);
	return(1);
}
void  fill_square(t_mlx *map, int width, int height, int color)
{
	int i;
	int j;

	i =	0;
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

void print_info(t_mlx *map)
{
	mlx_string_put(map->mlx, map->win, 30, 30, 0x74ebd5, "informations: ");
	mlx_string_put(map->mlx, map->win, 50, 70, 0xFFFFFF, "current fractal: ");
	mlx_string_put(map->mlx, map->win, 220, 70, 0xFFFFFF, map->argv);
	mlx_string_put(map->mlx, map->win, 50, 100, 0xFFFFFF, "mouse X: ");
	mlx_string_put(map->mlx, map->win, 140, 100, 0xFFFFFF, ft_itoa(map->info.mouse_x));
	mlx_string_put(map->mlx, map->win, 50, 130, 0xFFFFFF, "mouse Y: ");
	mlx_string_put(map->mlx, map->win, 140, 130, 0xFFFFFF, ft_itoa(map->info.mouse_y));
	mlx_string_put(map->mlx, map->win, 50, 160, 0xFFFFFF, "Max iterations: ");
	mlx_string_put(map->mlx, map->win, 210, 160, 0xFFFFFF, ft_itoa(map->f.MaxIterations));
//	mlx_string_put(map->mlx, map->win, 30, 180, 0xFFFFFF, ft_itoa(map->fac.count));
}
void draw_ui(t_mlx *map)
{
	mlx_put_image_to_window(map->mlx, map->win,
					map->ui_img.img_ptr, 0, 0);
	print_info(map);

}

void 		init_ui(t_mlx *map)
{
	init_image_ui(map, MENU_WIDTH, MENU_HEIGHT);
	fill_square(map, MENU_WIDTH, MENU_HEIGHT, 0x2f181818);
	draw_ui(map);
}

int			main(int argc, char *argv[])
{
  	t_mlx	map;
	map.index = 0;
	map.freez = 0;
	map.trigger = 0;
	map.info.mouse_x = 0;
	map.info.mouse_y = 0;
	map.fac.count = 0;
	map.animated = 0;
	map.mlx = mlx_init();
	map.win = mlx_new_window(map.mlx, WIN_WIDTH, WIN_HEIGHT,
			"is this shit working?");
	if (argc != 2)
	{
			ft_putstr("wrong arguments numbers\n");
			//add usage;
			return (-1);
	}
	if (argc == 2)
	{
		map.argv = argv[1];
		check_input(&map);
		init_fractol(&map);
	}
	init_image(&map, IMG_WIDTH, IMG_HEIGHT);
	init_ui(&map);
	escape_time(&map);
	//draw(&map);
	mlx_key_hook(map.win, key_down, &map);
	mlx_hook(map.win, 2, 0, key_long_press, &map);
	mlx_hook(map.win, 4, 0, mouse_wheel, &map);
	mlx_hook(map.win, 6, 0, mouse_move, &map);
	//mlx_loop_hook(map.mlx, mlx_while, &map);

//	mlx_loop_hook(map.mlx, print_usage_real_time, &map);
	mlx_loop(map.mlx);
	return (0);
}
