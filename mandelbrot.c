#include "fractol.h"

int 	key_hook(int keycode, t_env *e)
{
	printf("key = %d\n", keycode);
	if (keycode == 53)
		exit(0);
	return (e->bpp);
}

void	put_pixel_to_img(t_env *e, int x, int y, uint32_t color)
{
	int	octet;
	int	position;

	octet = e->sizeline / WIDTH;
	position = (e->sizeline * y) + (x * octet);
	ft_memcpy(e->data + position, &color, octet);
}

int 	expose_hook(t_env *e)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < WIDTH)
	{
		x = 0;
		while (x < HEIGHT) 
		{
			put_pixel_to_img(e, y, x, 0x00ced1);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}

int		mandelbrot(void)
{
	t_env e;
	//t_img i;

	e.mlx = mlx_init();
	if (e.mlx == NULL)
		exit(0);
	e.win = mlx_new_window(e.mlx, WIDTH, HEIGHT, "Fractol");
	mlx_key_hook(e.win, key_hook, &e);
	e.img = mlx_new_image(e.mlx, WIDTH, HEIGHT);
	e.data = mlx_get_data_addr(e.img, &e.bpp, &e.sizeline, &e.endian);
	mlx_expose_hook(e.win, expose_hook, &e);
	//mlx_hook(e.win, 6, (1L << 6), move_hook, &e);
	//mlx_mouse_hook(e.win, mouse_hook, &e);
	//mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}