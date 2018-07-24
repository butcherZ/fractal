#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include "../minilibx/mlx.h"

# define WIN_WIDTH 2000
# define WIN_HEIGHT 1000

# define IMG_WIDTH (WIN_WIDTH - 300)
# define IMG_HEIGHT WIN_HEIGHT

# define MENU_WIDTH 600
# define MENU_HEIGHT WIN_HEIGHT

# define JULIA 1
# define MANDELBROT 2
# define BURNINGSHIP 3

typedef struct	s_img
{
	void		*img_ptr;
	int			*addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int 		x;
	int			y;
}				t_img;

typedef	struct	s_fractal
{
	double MinRe;
	double MaxRe;
	double MinIm;
	double MaxIm;
	double Re_factor;
	double Im_factor;
	double c_re;
	double c_im;
	double z_re;
	double z_im;
	double z_re_square;
	double z_im_square;
	double cr;
	double ci;
	double real_diff;
	double img_diff;
	int isInside;
	int MaxIterations;
	int n;
}								t_fractal;

typedef struct 	s_factor
{
	double zoom;
	double		 x_translation;
	double		 y_translation;
	int		 increase_iterations;
	int 	 count;
}								t_factor;


typedef	struct  s_color
{
	int r;
	int g;
	int b;
	float t;
}								t_color;

typedef	struct	s_ui
{
	void		*img_ptr;
	int			*addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int 		x;
	int			y;
}				t_ui;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	//int			color;
  	t_img		img;
	t_fractal	f;
	t_factor fac;
	t_color color;
	t_ui		ui;
	int			trigger;
	int			index;
	int 		total; //total pixels;
	char    	*argv;
	int			input;
	int			animated;
	int			freez;
}				t_mlx;

/*
**  set up env for image set_up_image.c
*/

void			init_image(t_mlx *mlx, int width, int height);
void			img_put_pixel(t_mlx *mlx, int x, int y, int color);
void			empty(t_mlx *mlx);



#endif
