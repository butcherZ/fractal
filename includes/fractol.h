#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include "../minilibx/mlx.h"

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768

# define IMG_WIDTH WIN_WIDTH
# define IMG_HEIGHT WIN_HEIGHT

typedef struct	s_img
{
	void		*img_ptr;
	int			*addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
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
	int isInside;
	int MaxIterations;
}								t_fractal;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	int			color;
  t_img		img;
}				t_mlx;



/*
**  set up env for image set_up_image.c
*/

void			init_image(t_mlx *mlx);
void			img_put_pixel(t_mlx *mlx, int x, int y, int color);
void			empty(t_mlx *mlx);



#endif
