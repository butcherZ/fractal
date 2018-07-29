/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 13:25:52 by zyuan             #+#    #+#             */
/*   Updated: 2018/07/30 00:18:06 by zyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractol.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <string.h>

/*
 **	functions for setting up image.
*/

void		init_image(t_mlx *mlx, int width, int height)
{
	int		byte_per_pixel;

	byte_per_pixel = mlx->img.bits_per_pixel / 8;
	mlx->img.img_ptr = mlx_new_image(mlx->mlx, width, height);
	mlx->img.addr = (int*)mlx_get_data_addr(mlx->img.img_ptr,
			&mlx->img.bits_per_pixel, &mlx->img.size_line, &mlx->img.endian);
}

void		init_image_ui(t_mlx *mlx, int width, int height)
{
	int		byte_per_pixel;

	byte_per_pixel = mlx->ui_img.bits_per_pixel / 8;
	mlx->ui_img.img_ptr = mlx_new_image(mlx->mlx, width, height);
	mlx->ui_img.addr = (int*)mlx_get_data_addr(mlx->ui_img.img_ptr,
			&mlx->ui_img.bits_per_pixel, &mlx->ui_img.size_line,
			&mlx->ui_img.endian);
}

void		ui_img_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	if ((x >= 0 && x <= MENU_WIDTH) && (y >= 0 && y <= MENU_HEIGHT))
		mlx->ui_img.addr[y * (mlx->ui_img.size_line / 4) + x] = color;
}

void		img_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	if ((x >= 0 && x <= IMG_WIDTH) && (y >= 0 && y <= IMG_HEIGHT))
		mlx->img.addr[y * (mlx->img.size_line / 4) + x] = color;
}

/*
 **	Change all the pixels to black.
*/

void		empty(t_mlx *mlx)
{
	int		i;

	i = 0;
	while (i < IMG_HEIGHT * IMG_WIDTH)
	{
		mlx->img.addr[i] = 0;
		i++;
	}
}
