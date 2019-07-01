/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll_bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 12:20:35 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/06/07 12:04:36 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int		dragon_s(double x, double y, t_fractol *f)
{
	register int	i;
	double			y_temp;
	double			sq;
	double			prod;

	i = 0;
	f->p.x = f->w / f->h * (x - f->w / 3) / (0.15 * f->w) - 5.95;
	f->p.y = (y - f->h / 2) / (0.15 * f->h) - 1.3;
	f->img.c_re = 1.646;
	f->img.c_im = 0.967;
	while (f->p.x * f->p.x + f->p.y * f->p.y <= 4 && i < 256)
	{
		sq = f->p.y * f->p.y - f->p.x * f->p.x;
		prod = 2 * f->p.x * f->p.y;
		y_temp = f->img.c_im * (sq + f->p.x) - f->img.c_re * (prod - f->p.y);
		f->p.x = f->img.c_re * (sq + f->p.x) + f->img.c_im * (prod - f->p.y);
		f->p.y = y_temp;
		i++;
	}
	return (i);
}

static int		phoenix_set(double x, double y, t_fractol *f)
{
	int		i;
	double	x_temp;
	double	y_temp;
	double	x_old;
	double	y_old;

	i = 0;
	x_old = 1;
	y_old = 0;
	f->p.y = f->w / f->h * (x - f->w / 2) / (0.5 * 0.126446 * f->w) - 11.1;
	f->p.x = (y - f->h / 2) / (0.5 * 0.126446 * f->h) - 6.4;
	f->img.c_re = -0.270000;
	f->img.c_im = -0.316000;
	while (f->p.x * f->p.x + f->p.y * f->p.y < 4 && i < f->max_iter)
	{
		y_temp = 2 * f->p.x * f->p.y - f->img.c_im * y_old;
		x_temp = f->p.x * f->p.x - f->p.y * f->p.y - f->img.c_re
		- f->img.c_re * x_old;
		x_old = f->p.x;
		y_old = f->p.y;
		f->p.x = x_temp;
		f->p.y = y_temp;
		i++;
	}
	return (i);
}

static int		scroll_bar(double x, double y, t_fractol *f, int condition)
{
	int		iteration;

	iteration = 0;
	if (condition == 1)
		iteration = man_set(x, y, f);
	if (condition == 2)
		iteration = julia_set(x, y, f);
	if (condition == 3)
		iteration = newton_seventh_s(x, y, f);
	if (condition == 4)
		iteration = dragon_s(x, y, f);
	if (condition == 5)
		iteration = phoenix_set(x, y, f);
	return (iteration);
}

static void		set_scroll_bar(t_fractol f, double screen, int condition)
{
	double	x;
	double	y;
	int		iteration;

	y = screen * (condition - 1);
	while (y < condition * screen)
	{
		x = WIDTH - screen;
		while (x < WIDTH)
		{
			iteration = scroll_bar(x, y, &f, condition);
			if (iteration < 30)
				set_color(iteration, x, y, f);
			x++;
		}
		y++;
	}
}

void			f_set(t_fractol f)
{
	int		screen;

	screen = HEIGHT / 5;
	set_scroll_bar(f, screen, 1);
	set_scroll_bar(f, screen, 2);
	set_scroll_bar(f, screen, 3);
	set_scroll_bar(f, screen, 4);
	set_scroll_bar(f, screen, 5);
}
