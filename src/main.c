/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 07:09:24 by zyuan             #+#    #+#             */
/*   Updated: 2018/07/30 00:17:54 by zyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractol.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <string.h>

/*
** That is, I define that the minimum real part of the complex numbers that is
** the left border of the image) is -2.0 and the maximum (that is, the right
** border) is 1.0. This means that the real part of the complex numbers will go
** from -2.0 to 1.0.
** In the same way I defined that the lower border of the image is equivalent
** to the imaginary part -1.2.
** f(z) = z2 + c
*/

void		print_usage(void)
{
	ft_putstr("Usage: \n");
	ft_putstr("pass fractal's name as argument to lauch desired fractal\n");
	ft_putstr("Options are :\n");
	ft_putstr("- julia\n- mandelbrot\n- burningship\n");
	ft_putstr("Example: ./fractol julia\n");
}

void		check_input(t_mlx *map)
{
	char	*str1;
	char	*str2;
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
		ft_putstr("Sorry, my program is too stupid to generate this fractal\n");
		print_usage();
		map->input = 0;
	}
}

void		set_env(t_mlx *map)
{
	map->index = 0;
	map->freeze = OFF;
	map->info.mouse_x = 0;
	map->info.mouse_y = 0;
	map->fac.count = 0;
	map->menu = ON;
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, WIN_WIDTH, WIN_HEIGHT,
			"is this shit working?");
}

void		call_everything_in_main(t_mlx *map)
{
	set_env(map);
	init_image(map, IMG_WIDTH, IMG_HEIGHT);
	init_ui(map);
	escape_time(map);
	draw_ui(map);
}

int			main(int argc, char *argv[])
{
	t_mlx	map;

	if (argc != 2)
	{
		ft_putstr("wrong arguments numbers\n");
		print_usage();
		return (-1);
	}
	if (argc == 2)
	{
		map.argv = argv[1];
		check_input(&map);
		init_fractal(&map);
	}
	call_everything_in_main(&map);
	mlx_key_hook(map.win, key_down, &map);
	mlx_hook(map.win, 2, 0, key_long_press, &map);
	mlx_hook(map.win, 4, 0, mouse_click, &map);
	mlx_hook(map.win, 6, 0, mouse_move, &map);
	mlx_loop(map.mlx);
	return (0);
}
