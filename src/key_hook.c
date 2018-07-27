#include "mlx.h"
#include "fractol.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int			key_down(int keycode, t_mlx *map)
{
	if (keycode == 50)
	{
		init_fractal(map);
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
	draw_ui(map);
	return (1);
}

void		key_move_fractal (int keycode, t_mlx *map)
{
	double real_diff = fabs(map->f.MinRe - map->f.MaxRe) * 0.05;
	double img_diff = fabs(map->f.MinIm - map->f.MaxIm) * 0.05;
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
}
int			key_long_press(int keycode, t_mlx *map)
{
	key_move_fractal(keycode, map);
	if (keycode == 12)
	{
		map->f.MaxIterations += 1;
	}
	if (keycode == 13)
	{
		map->f.MaxIterations -= 1;
	}
	empty(map);
	escape_time(map);
	draw_ui(map);
	return (1);
}