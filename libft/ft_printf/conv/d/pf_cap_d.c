/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_cap_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:36:08 by rbalbous          #+#    #+#             */
/*   Updated: 2018/04/12 18:55:33 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	create(t_flags *flags, t_var *var, long int d)
{
	if (d < 0)
		addchar('-', var);
	else if (flags->plus || flags->space)
		addchar(flags->plus ? '+' : ' ', var);
	d = (d > 0) ? -d : d;
	flags->precision = addmchar('0', var, flags->precision);
	pf_itoa(d, flags, var);
}

static char	dinitialise(t_flags *flags, long int d)
{
	int		test;
	int		flag;
	int		apo;

	flags->len = pf_intlen(d, 10);
	test = (d < 0);
	apo = (flags->tsep != 0) * ((flags->len / 3) - (flags->len % 3 == 0));
	flag = ((flags->space || flags->plus) && !test);
	flags->precision -= (flags->len - test) + apo;
	flags->precision *= flags->precision > 0;
	flags->fwidth -= flags->len + flags->precision + flag + apo;
	flags->fwidth *= (flags->fwidth > 0);
	flags->len -= 1 * (d < 0);
	return (' ');
}

int			pf_cap_d(t_flags *flags, t_var *var, va_list ap)
{
	char		width;
	long int	d;

	d = va_arg(ap, long int);
	if (d == 0 && flags->precision == 0)
		return (pf_empty_d(flags, var));
	width = dinitialise(flags, d);
	if (!flags->minus)
	{
		if (flags->zero && !flags->isp)
		{
			flags->precision = flags->fwidth;
			flags->fwidth = 0;
		}
		flags->fwidth = addmchar(width, var, flags->fwidth);
		create(flags, var, d);
	}
	else
	{
		create(flags, var, d);
		flags->fwidth = addmchar(width, var, flags->fwidth);
	}
	return (0);
}
