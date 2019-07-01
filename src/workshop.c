/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workshop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 12:48:08 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/06/07 12:04:36 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int		phoenix(int x, int y, t_fractol *f)
{
	int		i;
	double	x_temp;
	double	y_temp;
	double	x_old;
	double	y_old;

	i = 0;
	x_old = 1;
	y_old = 0;
	f->p.y = f->w / f->h * (x - f->w / 2) / (0.5 * f->img.zoom * f->w)
			- f->img.step_x;
	f->p.x = (y - f->h / 2) / (0.5 * f->img.zoom * f->h) + f->img.step_y;
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

int		dragon(int x, int y, t_fractol *f)
{
	int		i;
	double	y_temp;
	double	sq;
	double	prod;

	i = 0;
	f->p.x = f->w / f->h * (x - f->w / 4) / (f->img.zoom * f->w)
			- f->img.step_x;
	f->p.y = (y - f->h / 2) / (f->img.zoom * f->h) + f->img.step_y;
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
	if (i >= 256)
		return ((int)((f->p.x * f->p.x + f->p.y * f->p.y) * 8)) % 7 + 9;
	else
		return (1);
}

int		julia(int x, int y, t_fractol *f)
{
	int		i;
	double	c_re;
	double	c_im;
	double	x_temp;
	double	y_temp;

	i = 0;
	f->p.x = f->w / f->h * (x - f->w / 2) / (f->img.zoom * f->w / 2)
			- f->img.step_x;
	f->p.y = (y - f->h / 2) / (f->img.zoom * f->h / 2) + f->img.step_y;
	c_re = f->img.c_re;
	c_im = f->img.c_im;
	while (f->p.x * f->p.x + f->p.y * f->p.y <= 4 && i < f->max_iter)
	{
		x_temp = f->p.x * f->p.x - f->p.y * f->p.y + c_re;
		y_temp = 2 * f->p.x * f->p.y + c_im;
		f->p.x = x_temp;
		f->p.y = y_temp;
		i++;
	}
	return (i);
}

double	mandelbrot(int x, int y, t_fractol *f)
{
	int		i;
	double	xin;
	double	yin;
	double	x_temp;

	i = 0;
	xin = 0;
	yin = 0;
	f->img.c_re = (x - f->w / 2.0) * 3.0 * f->img.zoom / f->w - f->img.step_x;
	f->img.c_im = (y - f->h / 2.0) * 3.0 * f->img.zoom / f->w + f->img.step_y;
	while (xin * xin + yin * yin <= 4 && i < f->max_iter)
	{
		x_temp = xin * xin - yin * yin + f->img.c_re - 0.5;
		yin = 2 * xin * yin + f->img.c_im;
		xin = x_temp;
		i++;
	}
	return (i);
}

void	set_fractal_step_one(t_fractol *f)
{
	f->type = 1;
	f->img.step_x = 0;
	f->img.step_y = 0;
	f->img.color1 = 0;
	f->img.color2 = 35;
	f->img.zoom = 1;
	f->img.c_re = -0.66000;
	f->img.c_im = -0.40000;
	f->max_iter = MAX_ITER;
	f->h = HEIGHT;
	f->w = WIDTH;
	f->thr_num = 4;
	f->p.x = 0;
	f->p.y = 0;
	f->s = f->h / 5;
}
