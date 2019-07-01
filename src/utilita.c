/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilita.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 21:58:02 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/06/06 21:58:02 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	usage(void)
{
	ft_putstr("Usage: ./fractol [name fractal]\n");
	ft_putstr("Options:\n");
	ft_putstr("\tmandelbrot   \tLaunch app with Mandelbrot set\n");
	ft_putstr("\tjulia        \tLaunch app with Julia set\n");
	ft_putstr("\tseven_newton \tLaunch app with seven Newton set\n");
	ft_putstr("\tdragon       \tLaunch app with Dragon curve set\n");
	ft_putstr("\tphoenix      \tLaunch app with Phoenix set\n");
	exit(0);
}

void	check_arg(int ac, char **av, t_fractol *f)
{
	if (ac != 2)
		usage();
	if (ac == 2)
	{
		if (ft_strequ("mandelbrot", av[1]))
			f->type = 1;
		else if (ft_strequ("julia", av[1]))
			f->type = 2;
		else if (ft_strequ("seven_newton", av[1]))
			f->type = 3;
		else if (ft_strequ("dragon", av[1]))
			f->type = 4;
		else if (ft_strequ("phoenix", av[1]))
			f->type = 5;
		else
			usage();
		f->flag = f->type;
	}
}

double	any_fract(int x, int y, t_fractol f)
{
	double		iteration;

	iteration = 0;
	if (f.type == 1)
		iteration = mandelbrot(x, y, &f);
	else if (f.type == 2)
		iteration = julia(x, y, &f);
	else if (f.type == 3)
		iteration = newton_seventh(x, y, &f);
	else if (f.type == 4)
		iteration = dragon(x, y, &f);
	else if (f.type == 5)
		iteration = phoenix(x, y, &f);
	return (iteration);
}

void	*fractals(void *thread)
{
	int			x;
	int			y;
	double		iteration;
	t_thread	*new_th;

	new_th = thread;
	y = new_th->index * HEIGHT / new_th->f.thr_num;
	while (y < HEIGHT / new_th->f.thr_num * (new_th->index + 1))
	{
		x = 0;
		while (x < WIDTH)
		{
			iteration = any_fract(x, y, new_th->f);
			if (iteration < new_th->f.max_iter)
				set_color(iteration, x, y, new_th->f);
			x++;
		}
		y++;
	}
	return (NULL);
}

void	threads(t_fractol *f)
{
	t_thread	*thread;
	int			i;

	thread = (t_thread*)malloc(sizeof(t_thread) * f->thr_num);
	i = 0;
	while (i < f->thr_num)
	{
		thread[i].index = i;
		thread[i].f = *f;
		pthread_create(&(thread[i].thrd), NULL, fractals, (void *)&thread[i]);
		i++;
	}
	while (i--)
		pthread_join(thread[i].thrd, NULL);
	free(thread);
}
