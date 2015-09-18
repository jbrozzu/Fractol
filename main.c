#include "fractol.h"

void	select_type(int type)
{
	if (type == 1)
		mandelbrot();
	else if (type == 1)
		return;
	else
		return;
}

int		get_name(char *name)
{
	if (ft_strcmp(name, "mandelbrot") == 0)
		return (1);
	else if (ft_strcmp(name, "julia") == 0)
		return (2);
	else
		return (0);
}

int		main(int argc, char **argv)
{
	int type;

	if (argc == 2)
	{
		type = get_name(argv[1]);
		if (type != 0)
			select_type(type);
		else
			ft_putstr("Mauvais Nom!\n");
	}
	else
		ft_putstr("Pas bon nombre argument!\n");
}