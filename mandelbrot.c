#include "fractol.h"

int 	key_hook(int keycode, t_env *e)
{
	printf("key = %d\n", keycode);
	if (keycode == 53)
		exit(0);
	if (keycode == 123)
		e->move_x -= 0.2;
	if (keycode == 124)
		e->move_x += 0.2;
	if (keycode == 126)
		e->move_y -= 0.2;
	if (keycode == 125)
		e->move_y += 0.2;
	expose_hook(e);
	return (0);
}

void	put_pixel_to_img(t_env *e, int x, int y, uint32_t color)
{
	int	octet;
	int	position;

	octet = e->sizeline / WIDTH;
	position = (e->sizeline * y) + (x * octet);
	ft_memcpy(e->data + position, &color, octet);
}

void	set_mandel(t_env *e)
{
	e->move_x = 0;
	e->move_y = 0;
}











int		fractal_mandelbrot(t_point *p)
{
	t_point	new;
	t_point	old;
	int		i;
	int 	iter;
	
	i = 0;
	iter = 500;
	new.a = 0;
	new.b = 0;
	while (i < iter)
	{
		old.a = new.a;
	 	old.b = new.b;
	 	new.a = old.a * old.a - old.b * old.b + p->a;
		new.b = 2 * old.a * old.b + p->b;
		if ((new.a * new.a + new.b * new.b) > 4)
			break ;
		i++;
	}
	if (i == iter)
		return (0);
	return (i);
}

int 	expose_hook(t_env *e)
{
	t_point	p;
	int 	color;
	int 	x;
	int 	y;
	
	e->color = 0x00003F;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			// Cx = CxMin + iX * PixelWidth;
			// Cy = CyMin + iY * PixelHeight;
			p.a = (x - WIDTH / 1.5) / (0.5 * WIDTH) + e->move_x;
	 		p.b = (y - HEIGHT / 2) / (0.5 * HEIGHT) + e->move_y;
	 		color = (e->color * (fractal_mandelbrot(&p) % 0xff));
	 		put_pixel_to_img(e, x, y, color);
	 		y++;
		}
		x++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}









int		mandelbrot(void)
{
	t_env e;

	e.mlx = mlx_init();
	if (e.mlx == NULL)
		exit(0);
	set_mandel(&e);
	e.win = mlx_new_window(e.mlx, WIDTH, HEIGHT, "Fractol");
	e.img = mlx_new_image(e.mlx, WIDTH, HEIGHT);
	e.data = mlx_get_data_addr(e.img, &e.bpp, &e.sizeline, &e.endian);
	mlx_clear_window(e.mlx, e.win);
	mlx_key_hook(e.win, key_hook, &e);
	mlx_expose_hook(e.win, expose_hook, &e);
	//mlx_hook(e.win, 6, (1L << 6), move_hook, &e);
	//mlx_mouse_hook(e.win, mouse_hook, &e);
	//mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}