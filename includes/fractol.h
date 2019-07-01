/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:47:26 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/06/13 14:51:07 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_2_FRACTOL_H
# define FRACTOL_2_FRACTOL_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <pthread.h>
# include "../libft/libft.h"

# define WIDTH 800
# define HEIGHT 500
# define MAX_ITER 30

typedef struct		s_color
{
	double			r;
	double			g;
	double			b;
}					t_color;

typedef struct		s_img
{
	void			*ptr;
	char			*str;
	int				bpp;
	int				s_l;
	int				endian;
	double			step_x;
	double			step_y;
	double			color1;
	double			color2;
	double			zoom;
	double			c_re;
	double			c_im;
}					t_img;

typedef struct		s_p
{
	double			x;
	double			y;
	double			z;
}					t_p;

typedef struct		s_fractol
{
	int				max_iter;
	void			*mlx_ptr;
	void			*win_ptr;
	int				type;
	double			w;
	double			h;
	double			s;
	int				flag;
	int				check_button;
	int				thr_num;
	t_p				p;
	t_img			img;
	struct s_thread	*thread;
}					t_fractol;

typedef struct		s_thread
{
	int				index;
	pthread_t		thrd;
	t_fractol		f;
}					t_thread;

void				f_set(t_fractol f);
double				mandelbrot(int x, int y, t_fractol *f);
int					julia(int x, int y, t_fractol *f);
int					newton_seventh(int x, int y, t_fractol *f);
int					phoenix(int x, int y, t_fractol *f);
int					dragon(int x, int y, t_fractol *f);
void				set_color(double i, double x, double y, t_fractol f);
int					man_set(double x, double y, t_fractol *f);
int					julia_set(double x, double y, t_fractol *f);
int					newton_seventh_s(int x, int y, t_fractol *f);
void				set_fractal_step_two(t_fractol *f);
void				set_keys_one(t_fractol *f, int key);
void				set_keys_two(t_fractol *f, int key);
void				but_4(t_fractol *f, int x, int y);
void				but_5(t_fractol *f, int x, int y);
void				check_arg(int ac, char **av, t_fractol *f);
void				threads(t_fractol *f);
void				set_fractal_step_one(t_fractol *f);
int					exit_out(t_fractol *f);

#endif
