/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seven_newton.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 21:26:24 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/06/07 12:04:36 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

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

int				newton_seventh(int x, int y, t_fractol *f)
{
	int		i;
	double	y_temp;
	double	x_old;
	double	y_old;

	i = 0;
	f->p.x = f->w / f->h * (x - f->w / 2) / (f->img.zoom * f->w / 2)
			- f->img.step_x;
	f->p.y = (y - f->h / 2) / (f->img.zoom * f->h / 2) + f->img.step_y;
	x_old = 42;
	y_old = 42;
	while (i < f->max_iter)
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
