/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll_bar_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 21:42:14 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/06/07 16:13:31 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int				man_set(double x, double y, t_fractol *f)
{
	int		i;
	double	xin;
	double	yin;
	double	x_temp;

	i = 0;
	xin = 0;
	yin = 0;
	f->img.c_re = (x - WIDTH / 2.0) * 3.0 * 6.0 / WIDTH - 8.0;
	f->img.c_im = (y - HEIGHT / 2.0) * 3.0 * 6.0 / WIDTH + 4.5;
	while (xin * xin + yin * yin <= 4 && i < 30)
	{
		x_temp = pow(xin, 2) - pow(yin, 2) + f->img.c_re - 0.5;
		yin = 2 * xin * yin + f->img.c_im;
		xin = x_temp;
		i++;
	}
	return (i);
}

int				julia_set(double x, double y, t_fractol *f)
{
	int		i;
	double	x_temp;
	double	y_temp;

	i = 0;
	f->p.x = 1.5 * (x - f->w * 0.94) / (0.5 * 0.14 * f->w);
	f->p.y = (y - f->h * 0.3) / (0.5 * 0.14 * f->h);
	f->img.c_re = -0.66000;
	f->img.c_im = -0.40000;
	while (f->p.x * f->p.x + f->p.y * f->p.y <= 4 && i < 30)
	{
		x_temp = f->p.x * f->p.x - f->p.y * f->p.y + f->img.c_re;
		y_temp = 2 * f->p.x * f->p.y + f->img.c_im;
		f->p.x = x_temp;
		f->p.y = y_temp;
		i++;
	}
	return (i);
}

static double	temp(t_fractol *f, int count)
{
	double	sq_sum;
	double	div;

	sq_sum = f->p.x * f->p.x + f->p.y * f->p.y;
	div = 7.0 * (sq_sum * sq_sum * sq_sum * sq_sum * sq_sum * sq_sum);
	if ((div > -0.00004) && (div < 0.00004))
		div = 0.00004;
	if (count == 1)
	{
		return (0.85714285 * f->p.y -
		(6.0 * f->p.x * f->p.x * f->p.x * f->p.x * f->p.x * f->p.y
		- 20.0 * f->p.x * f->p.x * f->p.x * f->p.y * f->p.y * f->p.y
		+ 6.0 * f->p.x * f->p.y * f->p.y * f->p.y * f->p.y * f->p.y) / div);
	}
	else
	{
		return (0.85714285 * f->p.x
		+ (f->p.x * f->p.x * f->p.x * f->p.x * f->p.x * f->p.x
		- 15.0 * f->p.x * f->p.x * f->p.x * f->p.x * f->p.y * f->p.y
		+ 15.0 * f->p.x * f->p.x * f->p.y * f->p.y * f->p.y * f->p.y
		- f->p.y * f->p.y * f->p.y * f->p.y * f->p.y * f->p.y) / div);
	}
}

int				newton_seventh_s(int x, int y, t_fractol *f)
{
	int		i;
	double	y_temp;
	double	x_old;
	double	y_old;

	i = 0;
	f->p.x = f->w / f->h * (x - f->w / 2) / (0.5 * 0.0042 * f->w) - 333;
	f->p.y = (y - f->h / 2) / (0.5 * 0.0042 * f->h);
	x_old = 42;
	y_old = 42;
	while (i < 30)
	{
		y_temp = temp(f, 1);
		f->p.x = temp(f, 0);
		f->p.y = y_temp;
		if (fabs(x_old - f->p.x) < 1E-10 && (fabs(y_old - f->p.y) < 1E-10))
			break ;
		x_old = f->p.x;
		y_old = f->p.y;
		i++;
	}
	return (i);
}

int				exit_out(t_fractol *f)
{
	mlx_destroy_window(f->mlx_ptr, f->win_ptr);
	exit(0);
}
