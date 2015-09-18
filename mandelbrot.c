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












int		fractal_mandelbrot(t_point *p)
{
	t_point	new;
	t_point	old;
	int		i;
	int 	iter;
	
	i = 0;
	iter = 150;
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


	// t_complexe	old;
	// t_complexe	new;
	// int			i;

	// i = 0;
	// new.r = 0;
	// new.i = 0;
	// while (i < e->iter)
	// {
	// 	old.r = new.r;
	// 	old.i = new.i;
	// 	new.r = old.r * old.r - old.i * old.i + p->r;
	// 	new.i = 2 * old.r * old.i + p->i;
	// 	if ((new.r * new.r + new.i * new.i) > 4)
	// 		break ;
	// 	i++;
	// }
	// if (i == e->iter)
	// 	return (0);
	// return (i);
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
			p.a = 1.5 * (x - WIDTH / 2) / (0.5 * WIDTH);
	 		p.b = (y - HEIGHT / 2) / (0.5 * HEIGHT);
	 		color = (e->color * (fractal_mandelbrot(&p) % 0xff));
	 		put_pixel_to_img(e, x, y, color);
	 		y++;
		}
		x++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);




	// p.a = 0;
	// p.b = 0;
	// e->color = 0xff0000;
	// while (p.b < WIDTH)
	// {
	// 	p.a = 0;
	// 	while (p.a < HEIGHT) 
	// 	{
	// 		color = (e->color  * (fractal_mandelbrot(&p)));
	// 		put_pixel_to_img(e, p.b, p.a, color);
	// 		p.a++;
	// 	}
	// 	p.b++;
	// }
	// mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	// return (0);

	// t_complexe	p;
	// int			color;
	// int			x;
	// int			y;

	// x = 0;
	// while (x < H)
	// {
	// 	y = 0;
	// 	while (y < H)
	// 	{
	// 		p.r = 1.5 * (x - H / 2) / (0.5 * e->z * H) + e->movex;
	// 		p.i = (y - H / 2) / (0.5 * e->z * H) + e->movey;
	// 		color = (e->col * (ft_is_mandel(&p, e) % 0xff));
	// 		ft_put_pixel(e, x, y, color);
	// 		y++;
	// 	}
	// 	x++;
	// }
}









int		mandelbrot(void)
{
	t_env e;

	e.mlx = mlx_init();
	if (e.mlx == NULL)
		exit(0);
	e.win = mlx_new_window(e.mlx, WIDTH, HEIGHT, "Fractol");
	e.img = mlx_new_image(e.mlx, WIDTH, HEIGHT);
	e.data = mlx_get_data_addr(e.img, &e.bpp, &e.sizeline, &e.endian);
	mlx_key_hook(e.win, key_hook, &e);
	mlx_expose_hook(e.win, expose_hook, &e);
	//mlx_hook(e.win, 6, (1L << 6), move_hook, &e);
	//mlx_mouse_hook(e.win, mouse_hook, &e);
	//mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_loop(e.mlx);
	return (0);
}