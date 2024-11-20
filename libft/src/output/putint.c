/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:03:30 by cgama             #+#    #+#             */
/*   Updated: 2024/07/31 13:03:35 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	put_i(char *nbstr, int n, t_flags flags)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		if (flags.zero == 0 || flags.precision >= 0)
			count += ft_putchar('-');
	}
	else if (flags.plus == 1 && flags.zero == 0)
		count += ft_putchar('+');
	else if (flags.space == 1 && flags.zero == 0)
		count += ft_putchar(' ');
	if (flags.precision >= 0)
		count += putspace(flags.precision - 1,
				ft_strlen(nbstr) - 1, 1);
	count += putstr(nbstr);
	return (count);
}

int	putsign(int n, t_flags *flags)
{
	int	count;

	count = 0;
	if (n < 0 && flags->precision == -1)
	{
		count += ft_putchar('-');
		flags->width--;
	}
	else if (flags->plus == 1)
		count += ft_putchar('+');
	else if (flags->space == 1)
	{
		count += ft_putchar(' ');
		flags->width--;
	}
	return (count);
}

int	putinteger(char *nbstr, int n, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.zero == 1)
		count += putsign(n, &flags);
	if (flags.left == 1)
		count += put_i(nbstr, n, flags);
	if (flags.precision >= 0 && (size_t)flags.precision < ft_strlen(nbstr))
		flags.precision = ft_strlen(nbstr);
	if (flags.precision >= 0)
	{
		flags.width -= flags.precision;
		if (n < 0 && flags.left == 0)
			flags.width -= 1;
		count += putspace(flags.width, 0, 0);
	}
	else
		count += putspace(flags.width - flags.plus - flags.space,
				ft_strlen(nbstr), flags.zero);
	if (flags.left == 0)
		count += put_i(nbstr, n, flags);
	return (count);
}

int	putint(int n, t_flags flags)
{
	char	*nbstr;
	long	nb;
	int		count;

	nb = n;
	count = 0;
	if (nb < 0)
	{
		nb *= -1;
		if (flags.zero == 0)
			flags.width--;
	}
	if (flags.precision == 0 && n == 0)
	{
		count += putspace(flags.width, 0, 0);
		return (count);
	}
	nbstr = itoa(nb);
	if (!nbstr)
		return (0);
	count += putinteger(nbstr, n, flags);
	free(nbstr);
	return (count);
}
