/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 07:27:52 by zyuan             #+#    #+#             */
/*   Updated: 2018/07/27 07:40:10 by zyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include "../minilibx/mlx.h"

# define WIN_WIDTH 1300
# define WIN_HEIGHT 800

# define IMG_WIDTH WIN_WIDTH
# define IMG_HEIGHT WIN_HEIGHT

# define MENU_WIDTH WIN_WIDTH / 4
# define MENU_HEIGHT WIN_HEIGHT

# define JULIA 2
# define MANDELBROT 3
# define BURNINGSHIP 4

# define ON 1
# define OFF 0

# define DEFAULT 5
# define STAR_DUST 6
# define BLOODY_HELL 7
# define CRAZY_MODE 8

typedef struct	s_img
{
	void		*img_ptr;
	int			*addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			x;
	int			y;
}				t_img;

typedef	struct	s_fractal
{
	double		min_re;
	double		max_re;
	double		min_im;
	double		max_im;
	double		re_factor;
	double		im_factor;
	double		c_re;
	double		c_im;
	double		z_re;
	double		z_im;
	double		z_re_square;
	double		z_im_square;
	double		cr;
	double		ci;
	double		real_diff;
	double		img_diff;
	int			is_inside;
	int			max_iterations;
	int			n;
}				t_fractal;

typedef struct	s_factor
{
	double		zoom;
	double		x_translation;
	double		y_translation;
	int			count;
}				t_factor;

typedef	struct	s_color
{
	int			r;
	int			g;
	int			b;
	float		t;
	int			color_style;
}				t_color;

typedef	struct	s_info
{
	int			mouse_x;
	int			mouse_y;
	int			mouse_button;
}				t_info;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		ui_img;
	t_fractal	f;
	t_factor	fac;
	t_color		color;
	t_info		info;
	int			trigger;
	int			index;
	int			total;
	char		*argv;
	int			input;
	int			animated;
	int			menu;
	int			freeze;
}				t_mlx;

/*
**  set up env for image set_up_image.c
*/

void			init_image(t_mlx *mlx, int width, int height);
void			img_put_pixel(t_mlx *mlx, int x, int y, int color);
void			empty(t_mlx *mlx);
void			init_image_ui(t_mlx *mlx, int width, int height);
void			ui_img_put_pixel(t_mlx *mlx, int x, int y, int color);

/*
**  init fractals init_fractal.c
*/

void			init_mandelbrot(t_mlx *map);
void			init_julia(t_mlx *map);
void			init_burningship(t_mlx *map);
void			init_var(t_mlx *map);
void			init_fractal(t_mlx *map);

/*
**  core algorithem escape_time.c
*/

void			check_map(t_mlx *map);
void			loop_through(t_mlx *map);
void			set_factor(t_mlx *map);
void			increase_iterations(t_mlx *map);
void			escape_time(t_mlx *map);

/*
**  set colors and draw fractals color.c
*/

void			fill_square(t_mlx *map, int width, int height, int color);
unsigned long	create_rgb(int r, int g, int b);
void			get_color(t_mlx *map);
void			draw(t_mlx *map, int x, int y);

/*
**  draw ui and print info ui.c
*/

void			convert(t_mlx *map);
void			print_info(t_mlx *map);
void			print_control(t_mlx *map);
void			init_ui(t_mlx *map);
void			draw_ui(t_mlx *map);

/*
**  key_hook.c
*/
void			color_style(int keycode, t_mlx *map);
int				key_down(int keycode, t_mlx *map);
void			key_move_fractal (int keycode, t_mlx *map);
int				key_long_press(int keycode, t_mlx *map);

/*
**  mouse_hook.c
*/

void			translate_fractal(int x, int y, t_mlx *map);
int				mouse_move(int x, int y, t_mlx *map);
void			zoom_on_cursor(int button, int x, int y, t_mlx *map);
int				mouse_wheel(int button, int x, int y, t_mlx *map);

/*
**  main.c
*/

void			print_usage(void);
void			check_input(t_mlx *map);
void			set_env(t_mlx *map);
void			call_everything_in_main(t_mlx *map);
#endif
