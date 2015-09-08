#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "./minilibx_macos/mlx.h"
# include <fcntl.h>
# include <stdio.h>

#define WIDTH 500
#define HEIGHT 500

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	int			type;
	void		*img;
	int			width;
	int			height;
	char		*data;
	int			bpp;
	int			endian;
	int			sizeline;
}				t_env;

// typedef struct	s_img
// {
// 	void		*img;
// 	int			width;
// 	int			height;
// 	char		*data;
// 	int			bpp;
// 	int			endian;
// 	int			sizeline;
// }				t_img;

int		get_name(char *name);
void	select_type(int type);
void	put_pixel_to_img(t_env *e, int x, int y, uint32_t color);
int 	expose_hook(t_env *e);
int 	expose_hook(t_env *e);
int		mandelbrot(void);
int 	key_hook(int keycode, t_env *e);


#endif