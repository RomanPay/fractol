/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 21:55:43 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/06/06 21:55:46 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	set_fractal_step_two(t_fractol *f)
{
	f->img.step_x = 0;
	f->img.step_y = 0;
	f->img.color1 = 0;
	f->img.color2 = 35;
	f->img.zoom = 1;
	f->max_iter = MAX_ITER;
	f->img.c_re = -0.66000;
	f->img.c_im = -0.40000;
	f->p.x = 0;
	f->p.y = 0;
	f->check_button = 0;
}

void	set_keys_one(t_fractol *f, int key)
{
	if (key == 91)
		f->img.step_y += 0.1 * f->img.zoom;
	if (key == 84)
		f->img.step_y -= 0.1 * f->img.zoom;
	if (key == 86)
		f->img.step_x -= 0.1 * f->img.zoom;
	if (key == 88)
		f->img.step_x += 0.1 * f->img.zoom;
	if (key == 53)
		exit(0);
	if (key == 89)
		f->img.color1 += 0.01;
	if (key == 92)
		f->img.color1 -= 0.01;
	if (key == 83)
		f->img.color2 -= 0.0001;
	if (key == 85)
		f->img.color2 += 10;
	if (key == 78)
		f->img.zoom *= 1.1;
	if (key == 69)
		f->img.zoom /= 1.1;
	if (key == 12)
		f->img.c_re += 0.0002;
}

void	set_keys_two(t_fractol *f, int key)
{
	if (key == 13)
		f->img.c_re -= 0.0002;
	if (key == 0)
		f->img.c_im += 0.0002;
	if (key == 1)
		f->img.c_im -= 0.0002;
	if (key == 34)
		f->max_iter += 10;
	if (key == 18)
	{
		if (f->type == 5)
			f->type = 1;
		else if (f->type == 1)
			f->type = 2;
		else if (f->type == 2)
			f->type = 3;
		else if (f->type == 3)
			f->type = 4;
		else
			f->type = 5;
	}
}

void	but_4(t_fractol *f, int x, int y)
{
	if (f->type == 1)
	{
		f->img.zoom *= 1.1;
		if (x > f->w / 2)
			f->img.step_x -= (x - f->w / 2) / 2 / 100 * 0.1 * f->img.zoom;
		if (x < f->w / 2)
			f->img.step_x += (f->w / 2 - x) / 2 / 100 * 0.1 * f->img.zoom;
		if (y < f->h / 2)
			f->img.step_y += (y - f->h / 2) / 2 / 100 * 0.1 * f->img.zoom;
		if (y > f->h / 2)
			f->img.step_y -= (f->h / 2 - y) / 2 / 100 * 0.1 * f->img.zoom;
	}
	else
	{
		f->img.zoom /= 1.1;
		if (x > f->w / 2)
			f->img.step_x -= (x - f->w / 2) / 2 / 100 * 0.1 / f->img.zoom;
		if (x < f->w / 2)
			f->img.step_x += (f->w / 2 - x) / 2 / 100 * 0.1 / f->img.zoom;
		if (y < f->h / 2)
			f->img.step_y += (y - f->h / 2) / 2 / 100 * 0.1 / f->img.zoom;
		if (y > f->h / 2)
			f->img.step_y -= (f->h / 2 - y) / 2 / 100 * 0.1 / f->img.zoom;
	}
}

void	but_5(t_fractol *f, int x, int y)
{
	if (f->type == 1)
	{
		f->img.zoom /= 1.1;
		if (x > f->w / 2)
			f->img.step_x -= (x - f->w / 2) / 2 / 100 * 0.1 * f->img.zoom;
		if (x < f->w / 2)
			f->img.step_x += (f->w / 2 - x) / 2 / 100 * 0.1 * f->img.zoom;
		if (y < f->h / 2)
			f->img.step_y += (y - f->h / 2) / 2 / 100 * 0.1 * f->img.zoom;
		if (y > f->h / 2)
			f->img.step_y -= (f->h / 2 - y) / 2 / 100 * 0.1 * f->img.zoom;
	}
	else
	{
		f->img.zoom *= 1.1;
		if (x > f->w / 2)
			f->img.step_x -= (x - f->w / 2) / 2 / 100 * 0.1 / f->img.zoom;
		if (x < f->w / 2)
			f->img.step_x += (f->w / 2 - x) / 2 / 100 * 0.1 / f->img.zoom;
		if (y < f->h / 2)
			f->img.step_y += (y - f->h / 2) / 2 / 100 * 0.1 / f->img.zoom;
		if (y > f->h / 2)
			f->img.step_y -= (f->h / 2 - y) / 2 / 100 * 0.1 / f->img.zoom;
	}
}
