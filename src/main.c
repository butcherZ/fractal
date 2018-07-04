#include "mlx.h"
#include "fractol.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int			key_down(int keycode, t_mlx *map)
{
//	print_key_usage(keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(map->mlx, map->win);
		exit(1);
	}
	return (1);
}
/**
** That is, I define that the minimum real part of the complex numbers (that is,
** the left border of the image) is -2.0 and the maximum (that is, the right
** border) is 1.0. This means that the real part of the complex numbers will go
** from -2.0 to 1.0.
** In the same way I defined that the lower border of the image is equivalent to
** the imaginary part -1.2.
**/
void init_mandelbrot(t_fractal *f)
{
	f->MinRe = -2.0;
	f->MaxRe = 1.0;
	f->MinIm = -1.2;
	f->MaxIm = f->MinIm + (f->MaxRe - f->MinRe) * IMG_HEIGHT / IMG_WIDTH;
	f->Re_factor = (f->MaxRe - f->MinRe) / (IMG_WIDTH - 1);
	f->Im_factor = (f->MaxIm - f->MinIm) / (IMG_HEIGHT - 1);
	f->MaxIterations = 500;
}

unsigned long createRGB(int r, int g, int b)
{
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}
/*f(z) = z2 + c;*/
void mandelbrot(t_mlx *map)
{
	t_fractal f;

	init_mandelbrot(&f);
	int y = 0;

	while(y < IMG_HEIGHT)
	{
	    	f.c_im = f.MaxIm - y * f.Im_factor;
				int x = 0;
	    while(x<IMG_WIDTH)
	    {
	        f.c_re = f.MinRe + x * f.Re_factor;
					f.z_re = f.c_re;
					f.z_im = f.c_im;
	        f.isInside = 1;
					int n = 0;
	        while(n < f.MaxIterations)
	        {
							f.z_re_square = f.z_re * f.z_re;
							f.z_im_square = f.z_im * f.z_im;
	            if(f.z_re_square + f.z_im_square > 4)
	            {
	                f.isInside = 0;
	                break;
	            }
	            f.z_im = 2 * f.z_re * f.z_im + f.c_im;
	            f.z_re = f.z_re_square - f.z_im_square + f.c_re;
							n++;
					}
					printf("n is %d\n", n);
	        if(f.isInside == 1)
					{
					  img_put_pixel(map, x, y, 0);
					}
					else
					{
						img_put_pixel(map, x, y, createRGB(0xFF, 0xFF, 0xFF));
					}
					x++;
	    }
				y++;
	}
}
void  fill_screen(t_mlx *map)
{
	int i;
	int j;

	i =	0;
	j = 0;
	while (j < WIN_HEIGHT)
	{
		if (i < WIN_WIDTH)
		{
			img_put_pixel(map, i, j, 0XFFFFFF);
			i++;
		}
		else
		{
			i = 0;
			j++;
		}
	}
}

int			main(void)
{
  t_mlx	map;
	map.mlx = mlx_init();
	map.win = mlx_new_window(map.mlx, WIN_WIDTH, WIN_HEIGHT,
			"is this shit working?");
	init_image(&map);
	//fill_screen(&map);
	mandelbrot(&map);
	mlx_key_hook(map.win, key_down, &map);
	mlx_put_image_to_window(map.mlx, map.win,
			map.img.img_ptr, 0, 0);
	mlx_loop(map.mlx);
	return (0);
}
